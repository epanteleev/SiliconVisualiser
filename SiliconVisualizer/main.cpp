#include "Application.h"
#include <QtWidgets/QApplication>

#include <iostream>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	Application w;
	w.show();
	return a.exec();
}
