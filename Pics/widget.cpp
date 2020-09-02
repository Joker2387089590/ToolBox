#include "widget.h"
#include "ui_widget.h"
#include "tabpage.h"

#include <QEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QClipboard>
#include <QDebug>

// LBC : Left Button Click
// RBD : Right Button Double Click
// PDG : Press Drug
//
// +-----------+-----+-----------+-------------+-------+-------------+
// |           | LBC |    LBD    |     RBC     |  RBD  |     PDG     |
// +-----------+-----+-----------+-------------+-------+-------------+
// | label_pic | \\\ | MaxWindow | Show Bigger | Close | Move Window |
// +-----------+-----+-----------+-------------+-------+-------------+
// |   other   | \\\ | MaxWindow | \\\\\\\\\\\ | Close | Move Window |
// +-----------+-----+-----------+-------------+-------+-------------+

Widget::Widget(QWidget *parent) :
	QWidget(parent, Qt::FramelessWindowHint),
	ui(new Ui::Widget), curpage(nullptr)
{
	ui->setupUi(this);
	ui->widget->installEventFilter(this);
	ui->label_pic->installEventFilter(this);
	ui->label_curdir->installEventFilter(this);
	ui->tabWidget->installEventFilter(this);
	this->setMouseTracking(true);
	ui->widget->setMouseTracking(true);
	ui->label_pic->setMouseTracking(true);

	connect(ui->tabWidget, &QTabWidget::currentChanged, [this]()
	{
		if((curpage = dynamic_cast<tabpage*>(ui->tabWidget->currentWidget())))
			curpage->active();
	});
	connect(ui->button_dir, &QPushButton::clicked, [this]()
	{
		if(curpage)
		{
			curpage->setpath(QApplication::clipboard()->text());
			curpage->active();
		}
	});
}

void Widget::addTab(tabpage* page, const QString& title)
{
	page->w = this;
	page->pixlabel = ui->label_pic;
	ui->tabWidget->addTab(page, title);
}

bool Widget::eventFilter(QObject* obj, QEvent* event)
{
	using namespace Qt;
	auto mouseevent = dynamic_cast<QMouseEvent*>(event);
	static bool picmode = false;
	switch(auto et = event->type())
	{
	case QEvent::MouseButtonPress:
		oldmousepos = mouseevent->globalPos();
		oldwidgetpos = this->pos();
		if(mouseevent->button() == RightButton && obj == ui->label_pic && curpage)
		{
			if((picmode = !picmode))
			{
				this->setCursor(CrossCursor);
				curmousepos = oldmousepos;
			}
			else
			{
				this->setCursor(ArrowCursor);
				emit curpage->setpic();
			}
		}
		[[fallthrough]];
	case QEvent::MouseMove:
		if(picmode && curpage && !curpage->pix.isNull())
		{
			watchPic();
			if(et == QEvent::MouseButtonPress) return true;
			break;
		}
		if(mouseevent->buttons().testFlag(LeftButton)
		   && !windowState().testFlag(WindowMaximized))
			this->move(oldwidgetpos + QCursor::pos() - oldmousepos);
		break;
	case QEvent::MouseButtonDblClick:
		if(!picmode && mouseevent->button() == LeftButton)
		{
			setWindowState(windowState() == WindowNoState ?
							   WindowMaximized : WindowNoState);
			return true;
		}
		if(mouseevent->button() == RightButton) this->close();
		break;
	case QEvent::Resize:
		if (curpage)
		{
			ui->label_pic->resize(ui->widget->size());
			emit curpage->setpic();
		}
		break;
	default: break;
	}
	return QWidget::eventFilter(obj, event);
}

void Widget::pathText(tabpage* page, const QString& path)
{
	if(page == curpage) ui->label_curdir->setText(path);
}

void Widget::watchPic()
{
	int pw = curpage->pix.width(),
		ph = curpage->pix.height(),
		ww = ui->widget->width(),
		wh = ui->widget->height();
	auto wc = ui->widget->mapToGlobal(ui->widget->rect().center());

	// setup size of the window to cut pic
	QSize s(pw < ww ? pw : ww, ph < wh ? ph : wh);

	auto addpos = QCursor::pos() - oldmousepos;
	curmousepos += addpos;			// current mouse pos if not lock
	QCursor::setPos(oldmousepos);	// lock the mouse at oldmousepos

	// map current pos to widget coordinate
	auto picpos = ui->widget->mapFromGlobal(curmousepos);

	// get the distance from pos to widget's center
	auto distance = picpos - wc;

	// transform the distance to pic coordinate
	auto rate = (pw * wh) > (ph * ww) ? double(pw) / ww : double(ph) / wh;
	distance *= rate;

	// limit the distance to make the window totally locate in the pic
	int wallow = (pw - s.width()) / 2,
		hallow = (ph - s.height()) / 2;
	if(distance.x() < -wallow) distance.setX(-wallow);
	if(distance.x() > wallow) distance.setX(wallow);
	if(distance.y() < -hallow) distance.setY(-hallow);
	if(distance.y() > hallow) distance.setY(hallow);

	// now let picpos be pos of the window's topleft point
	picpos = QPoint(wallow, hallow) + distance;

	// cut the pic in rect(picpos, s)
	ui->label_pic->setPixmap(curpage->pix.copy(QRect(picpos, s)));

	// reverse the operation upon to move curmousepos to where it should be
	curmousepos = ui->widget->mapToGlobal(wc + distance / rate);
}

Widget::~Widget() { delete ui; }