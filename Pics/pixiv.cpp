#include "pixiv.h"
#include "ui_pixiv.h"

#define setconnect(button) connect(ui->button, &QPushButton::clicked, this, &pixiv::button)
static constexpr double rate = 1920.0 / 1080.0 / 1.3;

pixiv::pixiv(Widget* ins) :
	tabpage(ins), ui(new Ui::pixiv)
{
	ui->setupUi(this);
	setconnect(next);
	setconnect(change);
	setconnect(both);
	setconnect(skip);
	setpath("D:/图片/Saved Pictures/PxEz");
}

pixiv::~pixiv() { delete ui; }

void pixiv::next()
{
	tabpage::next();
	if(i == -1) return;
	if(pix.height() > rate * pix.width())
		sizetype = Mobile;
	else if(pix.width() > rate * pix.height())
		sizetype = PC;
	else
		sizetype = None;

	ui->info->setText(filelist[i].fileName() + " " + irformat);
	ui->change->setText("更改分类");
	ui->target->setText(QString::number(pix.width()) + " x " +
						QString::number(pix.height()) + " " +
						QMetaEnum::fromType<SizeTypes>().valueToKey(sizetype));
}

void pixiv::copy()
{
#ifndef QT_DEBUG
	QFile f(filelist[i].filePath());
	QString finalName = filelist[i].completeBaseName() + "." + irformat;
	if(sizetype.testFlag(Mobile)) f.copy(tars[1] + finalName);
	if(sizetype.testFlag(PC)) f.copy(tars[2] + finalName);
#endif
}

void pixiv::change()
{
	switch (sizetype)
	{
	case Mobile:
		sizetype = PC;
		ui->change->setText("改为PC");
		break;
	case PC:
		sizetype = Mobile;
		ui->change->setText("改为Mobile");
		break;
	default:
		sizetype = Mobile;
		ui->change->setText("改为Mobile");
		break;
	}
}
