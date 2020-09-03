#include <QApplication>
#include "Core.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setQuitOnLastWindowClosed(false);
	Core c;
	c.show();
	return a.exec();
}
