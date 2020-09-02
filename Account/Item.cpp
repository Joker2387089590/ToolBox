#include "Item.h"
#include "ui_Item.h"

using namespace Json::Interface;

Item::Item(const Object* object, QWidget* parent) :
	QWidget(parent),
	ui(new Ui::Item)
{
	ui->setupUi(this);

	ui->tag_label->setText("tag");
	ui->tag_edit->setText(object->at("tag")->cast<String>()->get());

	object->visit()(
	[this](const DT::String& key, const Node* value)
	{
		if(key == "tag") return;
		int row = ui->grid->rowCount();

		auto key_label = new QLabel(this);
		key_label->setText(key);
		ui->grid->addWidget(key_label, row, 0, 1, 1);

		auto value_lineedit = new QLineEdit(this);
		value_lineedit->setText(
			value->type() == NodeType::string ?
				value->cast<String>()->get() : value->text());
		ui->grid->addWidget(value_lineedit, row, 1, 1, 1);
	});
}

Item::~Item() { delete ui; }
