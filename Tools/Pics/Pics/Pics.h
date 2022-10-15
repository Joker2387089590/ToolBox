#ifndef PICS_H
#define PICS_H

#include <QWidget>
#include "../PicsGlobal.h"

namespace Ui { class Pics; }
class TabPage;

class PICS_EXPORT Pics : public QWidget
{
	Q_OBJECT

public:
	explicit Pics(QWidget* parent = nullptr);

	void addTab(TabPage* page, const QString& title = QString());
	void pathText(TabPage* page, const QString& path);
	~Pics() override;

protected:
	virtual bool eventFilter(QObject* obj, QEvent* event) override;

private:
	Ui::Pics* ui;
	TabPage* curpage;

	QPoint old_mouse_pos;
	QPoint old_widget_pos;
	QPoint cur_mouse_pos;

	void watchPic();
};

#endif // PICS_H


























