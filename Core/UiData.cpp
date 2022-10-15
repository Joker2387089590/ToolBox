#include "UiData.h"

namespace ToolBox::Cores
{
UiData::UiData(QObject* parent) : QObject(parent) {}

void UiData::addTool(const QString& tool)
{
	m_toolList.append(tool);
	emit toolAdded();
}
}
