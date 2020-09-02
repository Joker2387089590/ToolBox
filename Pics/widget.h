#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui { class Widget; }
class tabpage;
class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = nullptr);
	void addTab(tabpage* page, const QString& title = QString());
	void pathText(tabpage* page, const QString& path);
	~Widget() override;

protected:
	virtual bool eventFilter(QObject* obj, QEvent* event) override;

private:
	Ui::Widget* ui;
	QPoint oldmousepos, oldwidgetpos, curmousepos;
	void watchPic();
	tabpage* curpage;
};

#endif // WIDGET_H


























