#include "tabpage.h"
#include <QDir>
#include <QClipboard>
#include <QApplication>
#include <QtConcurrent/QtConcurrentRun>

tabpage::tabpage(Pics* ins)
	: QWidget(nullptr), w(ins), pixlabel(nullptr)
{
	ir.setDecideFormatFromContent(true);
	connect(this, &tabpage::setpic, [this]()
	{
		auto ff = QtConcurrent::run([this]()
		{
			if(!pix.isNull()) pixlabel->setPixmap(pix.scaled(
				pixlabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
		});
		while(!ff.isFinished())
			QApplication::processEvents(QEventLoop::AllEvents, 200);
	});
	if(ins) ins->addTab(this);
}

void tabpage::setpath(const QString& newpath)
{
	QDir libraryPath(newpath);
	if(libraryPath == QDir(path)) return;
	path = libraryPath.path();
	emit pathChanged();
	if(w) w->pathText(this, path);
	libraryPath.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	libraryPath.setSorting(QDir::NoSort);
	filelist = libraryPath.entryInfoList();
	i.mi = -1; next();
}

void tabpage::next()
{
	int s = filelist.size();
	if(s == 0)
	{
		path = "Invalid path!";
		return;
	}
	if(i >= 0) this->copy();
	if(++(i.mi) >= s) i.mi = 0;
	ir.setFileName(filelist[i].filePath());
	irformat = ir.format();
	pix = QPixmap::fromImageReader(&ir);
	if(pixlabel) emit setpic();
}

void tabpage::active()
{
	if(w) w->pathText(this, path);
	if(i != -1) emit setpic();
}
