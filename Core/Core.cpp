#include <QApplication>
#include <QTranslator>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include "Core.h"

namespace ToolBox::Cores
{
Core::Core() :
    QObject(nullptr),
	tray(new Tray),
	ui(new UiData(this)),
	root(nullptr),
	engine(new QQmlApplicationEngine(this)),
	account(new Accounts::Account(this)),
	exeIndex(new ExeIndexs::ExeIndex(this))
{
    addDefaultTrayAction();
	setupTools();
	initTranslations();
    setupQmlEngine();
}

Core::~Core() { delete tray; }

void Core::addDefaultTrayAction()
{
	tray->add(tr("Open"), [this](QAction* item) {
		connect(item, &QAction::triggered, this, &Core::show);
	});

	tray->add(tr("Exit"), [this](QAction* item) {
		connect(item, &QAction::triggered, qApp, &QApplication::quit);
	});
}

void Core::setupTools()
{
	connect(this, &Core::started, exeIndex, &ExeIndexs::ExeIndex::init);
	connect(exeIndex, &ExeIndexs::ExeIndex::inited, this, &Core::addTool);
	connect(exeIndex, &ExeIndexs::ExeIndex::toolAdded, ui, &UiData::addTool);

	connect(this, &Core::started, account, &Accounts::Account::init);
	connect(account, &Accounts::Account::inited, this, &Core::addTool);
	connect(account, &Accounts::Account::toolAdded, ui, &UiData::addTool);
}

void Core::initTranslations()
{
    QTranslator translator;
    for(auto& locale : QLocale::system().uiLanguages())
    {
        auto localeName = QLocale(locale).name();
        auto trFile = QString(":/i18n/%1_%2").arg("Core", localeName);
        if(translator.load(trFile))
        {
            qApp->installTranslator(&translator);
            break;
        }
    }
}

void Core::setupQmlEngine()
{
    auto context = engine->rootContext();
	context->setContextObject(ui);
    context->setContextProperty("tray", tray);
	engine->load(u"qrc:/Core/Core.qml"_qs);

	for(auto&& rootObj : engine->rootObjects())
	{
		if (rootObj->objectName() == "window")
		{
			root = rootObj;
			break;
		}
		else if(auto w = rootObj->findChild<QObject*>("window"))
		{
			root = w;
			break;
		}
	}
	if(!root) throw std::exception();
}

void Core::addTool(QQmlComponent* tool)
{
	root->setProperty("curTool", QVariant::fromValue(tool));
}
}
