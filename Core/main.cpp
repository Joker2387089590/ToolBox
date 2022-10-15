#include <cmath>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include "Core.h"

int main(int argc, char* argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
	// QApplication::setAttribute(Qt::AA_UseOpenGLES);
    // QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);


	QApplication a(argc, argv);

	using namespace ToolBox;
	Cores::Core m;

    return a.exec();
}
