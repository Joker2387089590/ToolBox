#ifndef HACG_H
#define HACG_H

#include "tabpage.h"

namespace Ui { class hacg; }

class hacg : public tabpage
{
	Q_OBJECT

public:
	explicit hacg(Pics* ins = nullptr);
	~hacg() override;
	virtual void next() override;
	virtual void copy() override;
	void del();
	static QString rename(const QFileInfo& fi);

private:
	Ui::hacg* ui;
	QString tar{ "D:/图片/幻灯片背景/" };
};

#endif // HACG_H
