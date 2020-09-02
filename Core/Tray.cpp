#include <QTimer>
#include "Tray.h"

Tray::Tray(QWidget* parent) :
	QSystemTrayIcon(parent),
	menu(new QMenu(parent))
{
	setIcon(QIcon(":/ToolBox.png"));
	setToolTip("ToolBox");
	setContextMenu(menu);
	QTimer::singleShot(0, this, &Tray::show);
	menu->addSeparator();
}

QAction* Tray::makeAction(const QString& text)
{
	auto r = new QAction(text, menu);
	menu->addAction(r);
	return r;
}

QMenu* Tray::getMenu() const
{
	return menu;
}
