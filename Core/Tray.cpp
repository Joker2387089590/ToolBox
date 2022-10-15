#include <QTimer>
#include <QApplication>
#include <QShowEvent>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include "Tray.h"
namespace ToolBox::Cores
{
class TrayPrivate
{
public:
	void activeTray(QSystemTrayIcon::ActivationReason r);

public:
	Tray* q;
	QSystemTrayIcon* icon;
	bool remain{false};
};

Tray::Tray(QWidget* parent) :
	QMenu(parent),
	d(new TrayPrivate{this, new QSystemTrayIcon(this)})
{
	// qApp->setQuitOnLastWindowClosed(false);
	d->icon->setIcon(QIcon(":/ToolBox.png"));
	d->icon->setToolTip("ToolBox");
	d->icon->setContextMenu(this);
	addSeparator();
	QTimer::singleShot(0, d->icon, &QSystemTrayIcon::show);
}

Tray::~Tray() { delete d; }

bool Tray::isRemainWhenShow() const
{
	return d->remain;
}

void Tray::setRemainWhenShow(bool value)
{
	d->remain = value;
	emit remainWhenShowChanged(value);
}

void Tray::add(const QString& text, const std::function<void(QAction*)>& init)
{
	init(this->addAction(text));
}

void TrayPrivate::activeTray(QSystemTrayIcon::ActivationReason r)
{
	switch (r)
	{
	case QSystemTrayIcon::Trigger: // Click
	case QSystemTrayIcon::DoubleClick:
		emit q->actived();
		break;

	case QSystemTrayIcon::Context: // Right Click
		q->show();
		break;

	default:
		break;
	}
}
}
