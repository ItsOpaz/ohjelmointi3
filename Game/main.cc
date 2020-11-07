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

    QImage bigMap = QImage(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    QImage smallMap = QImage(":/offlinedata/offlinedata/kartta_pieni_500x500.png");

    CourseSide::Logic game;
    game.fileConfig();

    std::shared_ptr<Students::City> manse(new Students::City());
    manse->setBackground(smallMap, bigMap);
    game.takeCity(manse);
    game.finalizeGameStart();

    Students::MainWindow mw;
    mw.show();
    mw.setPicture(bigMap);


    return a.exec();
}
