#pragma once
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include "Tray.h"
#include "UiData.h"

#include "Tools/Account/Account.h"
#include "Tools/ExeIndex/ExeIndex.h"

extern int main(int, char*[]);

namespace ToolBox::Cores
{
class Core : public QObject
{
    Q_OBJECT
private:
	friend int ::main(int, char*[]);
    explicit Core();
    ~Core();

public:
	void addTool(QQmlComponent* tool);

signals:
    void show();
	void started(QQmlContext* root, QQmlEngine* engine);

private:
	void addDefaultTrayAction();
	void setupTools();
	void initTranslations();
	void setupQmlEngine();

private:
	Tray* tray;
	UiData* ui;
	QObject* root;
	QQmlApplicationEngine* engine;

private:
	Accounts::Account* account;
	ExeIndexs::ExeIndex* exeIndex;
};
}
