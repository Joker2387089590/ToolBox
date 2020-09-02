#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <Interface.hpp>

namespace Ui { class Item; }

class Item : public QWidget
{
	Q_OBJECT
	Ui::Item* ui;

public:
	Item(const Json::Interface::Object* object, QWidget* parent);
	~Item();
};

#endif // ITEM_H
