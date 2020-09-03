#ifndef CGSORT_H
#define CGSORT_H

#include "tabpage.h"
#include <QMap>
#include <QDir>

namespace Ui { class cgsort; }

class cgsort : public tabpage
{
	Q_OBJECT

public:
	explicit cgsort(Pics *ins = nullptr);
	virtual ~cgsort() override;
	virtual void next() override;
	virtual void copy() override;
	void del();

signals:
	void sSave();
	void sDel();

private:
	Ui::cgsort *ui;
	bool ifskip;
	QMap<QString, int> charcount;

	class tarWrapper
	{
		QDir t;
	public:
		tarWrapper(const QString& ti) noexcept : t(ti) {}
		inline void setPath(const QString& ti) { t.setPath(ti); }
		inline QString path() const { return t.path() + '/'; }
	}tar;
};

#endif // CGSORT_H
