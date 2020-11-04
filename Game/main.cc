#include <QApplication>
#include "core/logic.hh"
#include "city.h"
#include "mainwindow.h"
#include "QImage"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    CourseSide::Logic game;
    game.fileConfig();
    std::shared_ptr<Students::City> Tampere(new Students::City());
    Tampere->setClock(QTime::currentTime());
    QImage bigMap = QImage(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    QImage smallMap = QImage(":/offlinedata/offlinedata/kartta_pieni_500x500.png");
    Tampere->setBackground(smallMap, bigMap);
    game.takeCity(Tampere);
    game.finalizeGameStart();

    MainWindow mw;
    mw.show();

    return a.exec();
}
