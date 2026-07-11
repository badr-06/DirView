#include <iostream>
#include <QDir>

int main(){

    QString str = QDir::homePath();
    std::cout << str.toStdString();

    return 0;
}