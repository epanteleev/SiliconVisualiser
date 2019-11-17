#include "Application.h"
#include <QtWidgets/QApplication>

#include <iostream>

int main(int argc, char *argv[]) {
    //std::cout<<static_cast<int>(0.5)<<std::endl;
	QApplication a(argc, argv);
	Application w;
	w.show();
	return a.exec();
}


