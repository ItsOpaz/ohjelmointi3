#include <QApplication>
#include "core/logic.hh"
#include "city.h"
#include "mainwindow.h"
#include "graphics/simplemainwindow.hh"
#include "QImage"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    CourseSide::Logic game;
    game.fileConfig();

    std::shared_ptr<Students::City> Tampere(new Students::City());
<<<<<<< HEAD
=======
    Tampere->setClock(QTime::currentTime());

>>>>>>> ee97eb8bf131956f6ac685f77bc4f0486499a723
    game.takeCity(Tampere);
    game.finalizeGameStart();

    QImage bigMap = QImage(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    QImage smallMap = QImage(":/offlinedata/offlinedata/kartta_pieni_500x500.png");

    Students::MainWindow mw;
    mw.show();
    mw.setPicture(bigMap);


    return a.exec();
}
