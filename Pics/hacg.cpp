#include "hacg.h"
#include "ui_hacg.h"
#include <QRegularExpression>

hacg::hacg(Widget* ins) : tabpage(ins), ui(new Ui::hacg)
{
	ui->setupUi(static_cast<QWidget*>(this));
	connect(ui->rename, &QPushButton::clicked, this, &hacg::next);
	connect(ui->del,	&QPushButton::clicked, this, &hacg::del);
	setpath("E:/.Joker/琉璃神社壁纸包/琉璃神社壁纸包 2019年11月号/");
}

hacg::~hacg() { delete ui; }

void hacg::next()
{
	tabpage::next();
	if(i == -1) return;
	ui->curname->setText(filelist[i].filePath());
	QString lnew = tar + rename(filelist[i]) + "." + irformat;
	ui->newname->setText(lnew);
}

void hacg::copy()
{
#ifndef QT_DEBUG
	QFile::copy(ui->curname->text(), ui->newname->text());
#endif
}

inline void hacg::del()
{
#ifndef QT_DEBUG
	QFile::remove(filelist[i].filePath());
#endif
	next();
}

QString hacg::rename(const QFileInfo& fi)
{
	QString newname;
	QRegularExpression re;
	QRegularExpressionMatch match;

	QString fp = fi.path();
	re.setPattern("(?<year>\\d{4}年)+(?<month>((0{0,1}\\d)|(1[012]))月)");
	match = re.match(fp);
	if(match.hasMatch())
		newname = match.captured("year") + " " + match.captured("month") + "-";
	else return QString("时间出错");

	QString fn = fi.fileName();
	re.setPattern("\\d+");
	match = re.match(fn);
	if(match.hasMatch()) newname += match.captured();
	else return QString("编号出错");

	return newname;
}
