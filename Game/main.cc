#include <QApplication>
#include "creategame.h"
#include "QImage"
#include "startwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    Students::startwindow sw;
    sw.exec();

    Students::CreateGame on;
    on.StartGame();

    return a.exec();
}
