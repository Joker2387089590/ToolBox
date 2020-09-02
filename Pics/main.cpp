#include "widget.h"
#include "pixiv.h"
#include "hacg.h"
#include "cgsort.h"

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
	Widget w; w.show();
	w.addTab(new pixiv, "Pixiv");
	w.addTab(new hacg, "神社壁纸");
	w.addTab(new cgsort, "CG筛选");
	return QApplication::exec();
}
