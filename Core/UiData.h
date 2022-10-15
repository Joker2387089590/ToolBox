#pragma once
#include <QtQml/QtQml>

namespace ToolBox::Cores
{
class UiData : public QObject
{
	Q_OBJECT
	QML_ELEMENT
	Q_PROPERTY(QStringList tools MEMBER m_toolList NOTIFY toolAdded)

public:
	explicit UiData(QObject* parent);
	void addTool(const QString& tool);

signals:
	void toolAdded();

private:
	QStringList m_toolList;
};
}
