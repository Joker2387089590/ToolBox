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

QMenu* Tray::getMenu() const { return menu; }

QAction* Tray::makeAction(const QString& text)
{
	auto r = new QAction(text, menu);
	menu->addAction(r);
	return r;
}

QAction* Tray::action(const QString& text) const
{
	for(auto ai : menu->actions())
		if(ai->text() == text) return ai;
	return nullptr;
}

void Tray::removeAction(const QString& text)
{
	if(auto a = action(text)) menu->removeAction(a);
}
