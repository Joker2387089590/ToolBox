#include "Pics.h"
#include "../Pixiv/Pixiv.h"
#include "../HACG/HACG.h"
#include "../CGSort/CGSort.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	//QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	qunsetenv("QT_SCALE_FACTOR");
	qunsetenv("QT_ENABLE_HIGHDPI_SCALING");
	qunsetenv("QT_SCALE_FACTOR_ROUNDING_POLICY");
	qunsetenv("QT_SCREEN_SCALE_FACTORS");
	QApplication a(argc, argv);
	Pics w; w.show();
	w.addTab(new Pixiv, "Pixiv");
	w.addTab(new HACG, "神社壁纸");
	w.addTab(new CGSort, "CG筛选");
	return QApplication::exec();
}
