#include <QEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QClipboard>
#include <QDebug>

#include "Pics.h"
#include "ui_Pics.h"
#include "../TabPage/TabPage.h"

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

Pics::Pics(QWidget *parent) :
	QWidget(parent, !parent ? Qt::FramelessWindowHint : Qt::WindowFlags()),
	ui(new Ui::Pics),
	curpage(nullptr)
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
				if((curpage = dynamic_cast<TabPage*>(ui->tabWidget->currentWidget())))
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

void Pics::addTab(TabPage* page, const QString& title)
{
	page->w = this;
	page->pixlabel = ui->label_pic;
	ui->tabWidget->addTab(page, title);
}

bool Pics::eventFilter(QObject* obj, QEvent* event)
{
	using namespace Qt;

	auto mouse_event = static_cast<QMouseEvent*>(event);
	static bool picmode = false;

	switch(auto et = event->type())
	{
	case QEvent::MouseButtonPress:
		// save the position where any mouse button was pressed
		old_mouse_pos = mouse_event->globalPos();
		old_widget_pos = this->pos();

		// right press on picture
		if(mouse_event->button() == RightButton &&
		   obj == ui->label_pic && curpage)
		{
			if(!picmode)
			{
				this->setCursor(CrossCursor);
				cur_mouse_pos = old_mouse_pos;
			}
			else
			{
				this->setCursor(ArrowCursor);
				emit curpage->setpic();
			}
			picmode = !picmode;
		}
		[[fallthrough]];
	case QEvent::MouseMove:
		if(picmode && curpage && !curpage->pic.isNull())
		{
			watchPic();
			if(et == QEvent::MouseButtonPress) return true;
			break;
		}
		if(mouse_event->buttons().testFlag(LeftButton)
		   && !windowState().testFlag(WindowMaximized))
			this->move(old_widget_pos + QCursor::pos() - old_mouse_pos);
		break;
	case QEvent::MouseButtonDblClick:
		if(!picmode && mouse_event->button() == LeftButton)
		{
			setWindowState(windowState() == WindowNoState ?
							   WindowMaximized : WindowNoState);
			return true;
		}
		if(mouse_event->button() == RightButton) this->close();
		break;
	case QEvent::Resize:
		if (curpage)
		{
			ui->label_pic->resize(ui->widget->size());
			emit curpage->setpic();
		}
		break;
	default:
		break;
	}
	return QWidget::eventFilter(obj, event);
}

void Pics::pathText(TabPage* page, const QString& path)
{
	if(page == curpage) ui->label_curdir->setText(path);
}

void Pics::watchPic()
{
	using std::max, std::min;

	int pw = curpage->pic.width();
	int ph = curpage->pic.height();
	int ww = ui->widget->width();
	int wh = ui->widget->height();
	auto wc = ui->widget->mapToGlobal(ui->widget->rect().center());

	// size of the window to cut pic
	QSize s(min(pw, ww), min(ph, wh));

	auto addpos = QCursor::pos() - old_mouse_pos;
	cur_mouse_pos += addpos;			// current mouse pos if not lock
	QCursor::setPos(old_mouse_pos);	// lock the mouse at oldmousepos

	// map current pos to widget coordinate
	auto picpos = ui->widget->mapFromGlobal(cur_mouse_pos);

	// get the distance from pos to widget's center
	auto distance = picpos - wc;

	// transform the distance to pic coordinate
	auto rate = (pw * wh) > (ph * ww) ? (double(pw) / ww) : (double(ph) / wh);
	distance *= rate;

	// limit the distance to make the window totally locate in the pic
	int wallow = (pw - s.width()) / 2;
	int hallow = (ph - s.height()) / 2;
	distance.setX(max(distance.x(), -wallow));
	distance.setX(min(distance.x(), wallow));
	distance.setY(max(distance.y(), -hallow));
	distance.setY(min(distance.y(), hallow));

	// now let picpos be pos of the window's topleft point
	picpos = distance + QPoint(wallow, hallow);

	// cut the pic in rect(picpos, s)
	ui->label_pic->setPixmap(curpage->pic.copy(QRect(picpos, s)));

	// reverse the operation upon to move curmousepos to where it should be
	cur_mouse_pos = ui->widget->mapToGlobal(wc + distance / rate);
}

Pics::~Pics() { delete ui; }
