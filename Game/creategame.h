#ifndef CREATEGAME_H
#define CREATEGAME_H

#include "core/logic.hh"
#include "city.h"
#include "bettermainwindow.h"
#include <QObject>

namespace Students {

class CreateGame : public QObject
{
    Q_OBJECT
public:
    CreateGame();
    void StartGame();

private:
    std::unique_ptr<CourseSide::Logic> logic_;
    std::shared_ptr<Students::City> city_;
    std::shared_ptr<Students::BetterMainWindow> mainwindow_;
    QImage bigMap = QImage(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    QImage smallMap = QImage(":/offlinedata/offlinedata/kartta_pieni_500x500.png");
};

}


#endif // CREATEGAME_H
