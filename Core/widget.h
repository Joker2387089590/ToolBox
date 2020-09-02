#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include "Tray.h"

class WidgetPrivate;
class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = nullptr);
	~Widget();

	bool isTrayRemainWhenShow() const;
	void setTrayRemainWhenShow(bool value);
	Tray* tray() const;

signals:
	void aboutToQuit();

protected:
	void showEvent(QShowEvent *event) override;
	void closeEvent(QCloseEvent *event) override;

private:
	WidgetPrivate* d;
};

#endif // WIDGET_H
