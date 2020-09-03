#include <QApplication>

#include "Core.h"
#include "UiCore.h"

Core::Core(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::Core),
	tray_icon(new Tray(this))
{
	ui->setupUi(this);
	initSideBar();
	initTrayAction();
}

template<typename W,
		 std::enable_if_t<std::is_convertible_v<W*, QWidget*>, int>>
void Core::changeWorkPanel(W*& w)
{
	if(!w)
	{
		w = new W(this);
		ui->work_panel->addWidget(w);
		// w->resize(w->sizeHint());
		ui->work_panel->indexOf(w);
	}
	ui->work_panel->setCurrentWidget(w);
}

void Core::initSideBar()
{
	connect(ui->caller_account, &QToolButton::clicked,
			[this](){ changeWorkPanel(account); });
	connect(ui->caller_pics, &QToolButton::clicked,
			[this](){ changeWorkPanel(pics); });
}

void Core::initTrayAction()
{
	auto open = tray_icon->makeAction("Open");
	connect(open, &QAction::triggered, this, &Core::show);

	auto exit = tray_icon->makeAction("Exit");
	connect(exit, &QAction::triggered, this, &Core::exitApp, Qt::QueuedConnection);
	connect(tray_icon, &Tray::activated, this, &Core::activeTray);
}

void Core::activeTray(QSystemTrayIcon::ActivationReason r)
{
	switch (r)
	{
	case QSystemTrayIcon::Trigger: // Click
	case QSystemTrayIcon::DoubleClick:
		this->show();
		break;
	case QSystemTrayIcon::Context: // Right Click
		tray_icon->getMenu()->show();
		break;
	default:
		break;
	}
}

Tray* Core::tray() { return tray_icon; }
bool Core::isTrayRemainWhenShow() const { return tray_remain_when_show; }
void Core::setTrayRemainWhenShow(bool value) { tray_remain_when_show = value; }

void Core::showEvent(QShowEvent* event)
{
	if(!tray_remain_when_show) tray_icon->hide();
	QWidget::showEvent(event);
}

void Core::closeEvent(QCloseEvent* event)
{
	tray_icon->show();
	event->accept();
}

void Core::exitApp()
{
	emit aboutToQuit();
	qApp->quit();
}

Core::~Core() { delete ui; }
