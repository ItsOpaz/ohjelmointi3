#include <QApplication>
#include "creategame.h"
#include "QImage"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    Students::CreateGame on;
    on.StartGame();

    return a.exec();
}
