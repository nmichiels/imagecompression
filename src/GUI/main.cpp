#include <QtGui/QApplication>
#include "beeldcompressieui.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BeeldCompressieUI w;
	w.show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	return a.exec();
}
