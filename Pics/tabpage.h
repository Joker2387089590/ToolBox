#ifndef TABPAGE_H
#define TABPAGE_H

#include <QLabel>
#include <QPushButton>
#include <QImageReader>
#include <QFileInfo>
#include <QTabWidget>

#include "PicsGlobal.h"
#include "Pics.h"

class PICS_EXPORT tabpage : public QWidget
{
	Q_OBJECT

public:
	explicit tabpage(Pics* ins = nullptr);
	void setpath(const QString& newpath);
	virtual void next();
	virtual void copy() = 0;
	void active();

signals:
	void setpic();
	void pathChanged();

protected:
	friend class Pics;

	// file controller
	QString path;
	QList<QFileInfo> filelist;
	class IndexWrapper
	{
		friend tabpage;
		int mi;
	public:
		IndexWrapper(int i) noexcept : mi(i) {}
		operator int() { return mi; }
	} i{-1};

	// picture loader
	QImageReader ir;
	QString irformat;
	QPixmap pix;

	// UI controller
	Pics* w;
	QLabel*	pixlabel {nullptr};
};

#endif // TABPAGE_H
