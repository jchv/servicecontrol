#include "servicecontrol.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ServiceControl w;
    w.show();

    return app.exec();
}

