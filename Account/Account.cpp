#include <QDebug>
#include "Account.h"
#include "ui_Account.h"
#include "Item.h"

using namespace Json::Interface;

Account::Account(QWidget* parent) :
	QWidget(parent, Qt::SubWindow),
	ui(new Ui::Account),
	file(new QFile("D:\\桌面\\Joker\\Info.json", this))
{
	ui->setupUi(this);

	file->open(QFile::ReadOnly);
	auto text = QString::fromUtf8(file->readAll());
	json.reset(textToJson(text));
	file->close();

	connect(ui->pushButton, &QPushButton::clicked, this, &Account::makeItems);
}

QSharedPointer<const Node> Account::getJson() const
{
	return json.staticCast<const Node>();
}

Account::~Account() { delete ui; }

void Account::addItem(const Object* item)
{
	auto lwi = new QListWidgetItem(ui->listWidget);
	auto one_item = new Item(item, ui->listWidget);
	lwi->setSizeHint(one_item->sizeHint());
	// ui->listWidget->addItem(lwi);
	ui->listWidget->setItemWidget(lwi, one_item);
}

void Account::makeItems()
{
	auto account_list = (*json)["Account"].cast<Array>();
	for(auto ai : account_list->get())
		addItem(ai->cast<Object>());
}
