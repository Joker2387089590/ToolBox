#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QQmlContext>
#include "Account.h"

namespace ToolBox::Accounts
{
Account::Account(QObject* parent) :
    QObject(parent),
    m_item{nullptr}
{
	QFile file(":/Tools/Account/new-info.json");
	if(!file.open(QFile::ReadOnly))
	{
		qCritical() << tr("Can't load JSON");
		return;
	}

	auto content = file.readAll();
    QJsonParseError error;
	auto doc = QJsonDocument::fromJson(content, &error);
    if(error.error != QJsonParseError::NoError)
	{
		qCritical() << "JSON prase error: " << error.errorString();
		return;
	}

    m_infos = doc.object();
}

Account::~Account() {}

void Account::init(QQmlContext* root, QQmlEngine* engine)
{
	auto context = new QQmlContext(root);
	context->setContextProperty("backend", this);

	QQmlComponent component(engine, QUrl(u"qrc:/Tools/Account/Account.qml"_qs));
	if(component.isError())
	{
		qDebug() << component.errorString();
		return;
	}
	auto item = qobject_cast<QQmlComponent*>(component.create(context));
	if(!item)
	{
		qDebug() << "Account tool create failed";
		return;
	}

	emit inited(item);
	emit toolAdded(tr("Account"));
}
}
