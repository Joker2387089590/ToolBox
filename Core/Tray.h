#ifndef TRAY_H
#define TRAY_H

#include <QSystemTrayIcon>
#include <QMenu>

class Tray : public QSystemTrayIcon
{
	Q_OBJECT

public:
	explicit Tray(QWidget *parent = nullptr);
	QMenu* getMenu() const;

	QAction* makeAction(const QString& text);
	QAction* action(const QString& text) const;
	void removeAction(const QString& text);

private:
	QMenu* menu;
};

#endif // TRAY_H
