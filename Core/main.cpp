#include <QApplication>

#include "widget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setQuitOnLastWindowClosed(false);
	Widget w;
	w.show();
	return a.exec();
}
