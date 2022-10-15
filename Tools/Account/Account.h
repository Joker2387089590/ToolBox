#pragma once
#include <QJsonObject>
#include <QtQml/QtQml>

namespace ToolBox::Accounts
{
class Account : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Account(QObject* parent = nullptr);
    ~Account();

public slots:
	void init(QQmlContext* root, QQmlEngine* engine);

signals:
	void inited(QQmlComponent* tool);
	void toolAdded(const QString& text);

private:
    QJsonObject m_infos;
    QQmlComponent* m_item;
};
}
