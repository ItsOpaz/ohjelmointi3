#include "creategame.h"

QImage bigMap = QImage(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
QImage smallMap = QImage(":/offlinedata/offlinedata/kartta_pieni_500x500.png");

namespace Students
{
CreateGame::CreateGame():
    logic_(new CourseSide::Logic),
    city_(new Students::City),
    mainwindow_(new Students::BetterMainWindow)
{
    logic_->fileConfig();
    city_->takeMainWindow(mainwindow_);
    logic_->takeCity(city_);
    city_->setBackground(smallMap, bigMap);
}

void CreateGame::StartGame()
{
    logic_->finalizeGameStart();
}
}
