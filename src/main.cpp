#include <QApplication>
#include "MainWindow.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    MainWindow window(1000, 700);
    window.show();
    
    return app.exec();
}