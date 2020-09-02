#ifndef PIXIV_H
#define PIXIV_H

#include "tabpage.h"
#include <QMetaEnum>

namespace Ui { class pixiv; }

class pixiv : public tabpage
{
	Q_OBJECT

public:
	explicit pixiv(Widget* ins = nullptr);
	virtual ~pixiv() override;

	void change();
	virtual void next() override;
	virtual void copy() override;
	inline void both() { sizetype = Both; next(); }
	inline void skip() { sizetype = None; next(); }

	enum SizeType
	{
		None = 0,
		Mobile = 1,
		PC = 2,
		Both = Mobile | PC
	};
	Q_DECLARE_FLAGS(SizeTypes, SizeType)
	Q_FLAG(SizeTypes)

private:
	Ui::pixiv* ui;
	QString tars[3]
	{
		"D:/图片/Saved Pictures/Mobile/",
		"D:/图片/Saved Pictures/PC/",
		"D:/图片/Saved Pictures/None/"
	};
	SizeTypes sizetype;
};

#endif // PIXIV_H
