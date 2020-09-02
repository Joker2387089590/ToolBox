#include "cgsort.h"
#include "ui_cgsort.h"
#include <QKeyEvent>
#include <QFile>
#include <QApplication>
#include <QClipboard>

cgsort::cgsort(Widget *ins) :
	  tabpage(ins),
	  ui(new Ui::cgsort), tar(path)
{
	ui->setupUi(this);
	connect(ui->bSave,	 &QPushButton::clicked, this, &cgsort::next);
	connect(ui->bDelete, &QPushButton::clicked, this, &cgsort::del);
	connect(ui->bSkip,	 &QPushButton::clicked, [this](){ ifskip = true; next(); });
	connect(ui->bTarget, &QPushButton::clicked,
			[this](){ tar.setPath(QApplication::clipboard()->text()); });
	connect(this,		 &tabpage::pathChanged,
			[this](){ charcount.clear(); tar.setPath(path); });

	connect(ui->tName, &QLineEdit::textEdited,
			[this](const QString& charname)
			{
				auto no = QString::number(charcount[charname] + 1);
				ui->lTarget->setText(tar.path() + charname + "/" + no + "." + irformat);
			});
	setpath("E:/.Joker/GalgameTool/outPath/Navel/月に寄りそう乙女の作法/画像");
}

cgsort::~cgsort() { delete ui; }

void cgsort::next()
{
	tabpage::next();
	if(i == -1) return;
	ui->lSource->setText(filelist[i].filePath());

	QString charname = ui->tName->text();
	QString tarname;
	if(!charname.isEmpty())
	{
		auto no = QString::number(++charcount[charname]);
		tarname = tar.path() + charname + "/" + no + "." + irformat;
	}
	else tarname = tar.path() + filelist[i].fileName();
	ui->lTarget->setText(tarname);
}

inline void cgsort::del()
{
#ifndef QT_DEBUG
	QFile::remove(ui->lSource->text());
#endif
	next();
}

void cgsort::copy()
{
#ifndef QT_DEBUG
	if(ifskip)
	{
		QFile::copy(ui->lSource->text(), ui->lTarget->text());
		ifskip = false;
	}
#endif
}
