#ifndef TRAY_H
#define TRAY_H

#include <QSystemTrayIcon>
#include <QMenu>

class Tray : public QSystemTrayIcon
{
	Q_OBJECT

public:
	explicit Tray(QWidget *parent = nullptr);
	QAction* makeAction(const QString& text);
	QMenu* getMenu() const;

private:
	QMenu* menu;
};

#endif // TRAY_H
