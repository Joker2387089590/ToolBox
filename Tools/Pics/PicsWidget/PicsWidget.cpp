#include <QtConcurrent/QtConcurrentRun>
#include <QClipboard>

#include "../Pixiv/Pixiv.h"
#include "../HACG/HACG.h"
#include "../CGSort/CGSort.h"

#include "PicsWidget.h"
#include "ui_PicsWidget.h"

PicsWidget::PicsWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PicsWidget)
{
	ui->setupUi(this);
	connect(ui->clipboard, &QToolButton::clicked,
			[this]()
			{
				if(curpage)
					curpage->setDir(QApplication::clipboard()->text());
			});
	connect(ui->hacg, &QToolButton::clicked,
			[this]()
			{
				auto hacg = new HACG(this);
				addTab(hacg);
			});
}

PicsWidget::~PicsWidget()
{
	delete ui;
}

void PicsWidget::addTab(TabPage* tab)
{
	connect(tab, &TabPage::dirChanged,
			[tab, this](const QString& dir)
			{
				if(tab == curpage) ui->tab_dir->setText(dir);
			});
	connect(tab, &TabPage::picPrepared, this, &PicsWidget::loadPic);
	ui->tab_page->addWidget(tab);
	activeTab(tab);
}

void PicsWidget::activeTab(TabPage* tab)
{
	curpage = tab;
	ui->tab_dir->setText(tab->getDir());
}

void PicsWidget::loadPic()
{
	if(curpage != sender()) return;
	auto getSmooth = QtConcurrent::run(
		[this]()
		{
			ui->pic->setPixmap(curpage->getSmoothPic(ui->pic->size()));
		});
	while(!getSmooth.isFinished())
		QApplication::processEvents(QEventLoop::AllEvents, 200);
}

void PicsWidget::newDir(const QString& dir)
{
	if(curpage) curpage->setDir(dir);
}

bool PicsWidget::eventFilter(QObject* obj, QEvent* event)
{
	return true;
}
