#include "Application.h"
#include <QtWidgets/QApplication>

#include <iostream>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
    auto w = std::make_unique<Application>();
    w->show();
	return a.exec();
}
