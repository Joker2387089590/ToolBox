#ifndef PICS_WIDGET_H
#define PICS_WIDGET_H

#include <QWidget>
#include <QPixmap>
#include "../PicsGlobal.h"

namespace Ui { class PicsWidget; }
class TabPage;

class PicsWidget : public QWidget
{
	Q_OBJECT

public:
	explicit PicsWidget(QWidget *parent = nullptr);
	~PicsWidget();

	void addTab(TabPage* tab);
	void activeTab(TabPage* tab);

	void loadPic();
	void newDir(const QString& dir);

protected:
	bool eventFilter(QObject* obj, QEvent* event) override;

private:
	Ui::PicsWidget *ui;
	TabPage* curpage;
};

#endif // PICS_WIDGET_H
