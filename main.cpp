#include "headers/interface.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    TInterface window;
    window.show();

    return app.exec();
}