#include "qhangman.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QHangman w;
    w.show();

    return app.exec();
}

