#include <QMenu>
#include <QAction>
#include <QShowEvent>
#include <QCloseEvent>

#include "widget.h"
#include "ui_widget.h"

class WidgetPrivate
{
	Widget* const q;

public:
	Ui::Widget* const ui;
	Tray* const tray;
	bool trayRemainWhenShow{false};

	WidgetPrivate(Widget* parent) :
		q		(parent),
		ui		(new Ui::Widget),
		tray	(new Tray(parent))
	{
		ui->setupUi(q);
		initAction();
		QObject::connect(tray, &Tray::activated,
			std::bind(&WidgetPrivate::activeTray, this, std::placeholders::_1));
	}

	~WidgetPrivate() { delete ui; }

	void initAction()
	{
		auto open = tray->makeAction("Open");
		QObject::connect(open, &QAction::triggered, q, &Widget::show);

		auto exit = tray->makeAction("Exit");
		QObject::connect(exit, &QAction::triggered,
						 q,	   std::bind(&WidgetPrivate::exitApp, this),
						 Qt::QueuedConnection);
	}

	void activeTray(QSystemTrayIcon::ActivationReason r)
	{
		switch (r)
		{
		case QSystemTrayIcon::Trigger: // Click
		case QSystemTrayIcon::DoubleClick:
			q->show();
			break;
		case QSystemTrayIcon::Context: // Right Click
			tray->getMenu()->show();
			break;
		default:
			break;
		}
	}

	void exitApp()
	{
		emit q->aboutToQuit();
		qApp->quit();
	}

}; // class WidgetPrivate

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	d(new WidgetPrivate(this))
{
	connect(d->ui->trayControl, &QPushButton::clicked,
			[this]() { d->tray->showMessage("title", "message"); });
	connect(d->ui->makeItems, &QPushButton::clicked,
			d->ui->accountWidget, &Account::makeItems);
}

void Widget::showEvent(QShowEvent* event)
{
	if(!d->trayRemainWhenShow) d->tray->hide();
	QWidget::showEvent(event);
}

void Widget::closeEvent(QCloseEvent* event)
{
	d->tray->show();
	event->accept();
}

Tray* Widget::tray() const
{
	return d->tray;
}

bool Widget::isTrayRemainWhenShow() const
{
	return d->trayRemainWhenShow;
}

void Widget::setTrayRemainWhenShow(bool value)
{
	d->trayRemainWhenShow = value;
}

Widget::~Widget() { delete d; }
