#ifndef PICS_H
#define PICS_H

#include <QWidget>
#include "PicsGlobal.h"

namespace Ui { class Pics; }

class tabpage;

class PICS_EXPORT Pics : public QWidget
{
	Q_OBJECT

public:
	explicit Pics(QWidget* parent = nullptr);

	void addTab(tabpage* page, const QString& title = QString());
	void pathText(tabpage* page, const QString& path);
	~Pics() override;

protected:
	virtual bool eventFilter(QObject* obj, QEvent* event) override;

private:
	Ui::Pics* ui;
	tabpage* curpage;

	QPoint oldmousepos;
	QPoint oldwidgetpos;
	QPoint curmousepos;

	void watchPic();
};

#endif // PICS_H


























