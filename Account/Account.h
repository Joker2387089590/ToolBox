#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QWidget>
#include <QFile>
#include <QSharedPointer>
#include <Interface.hpp>
#include "Account_global.h"

namespace Ui { class Account; }

class ACCOUNT_EXPORT Account : public QWidget
{
	Q_OBJECT

public:
	explicit Account(QWidget* parent);
	~Account();

	QSharedPointer<const Json::Interface::Node> getJson() const;
	void makeItems();

private:
	Ui::Account* ui;
	QFile* file;
	QSharedPointer<Json::Interface::Node> json;

	void addItem(const Json::Interface::Object* item);
};

#endif // ACCOUNT_H
