#include "creategame.h"

QImage bigMap = QImage(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
QImage smallMap = QImage(":/offlinedata/offlinedata/kartta_pieni_500x500.png");

namespace Students
{
CreateGame::CreateGame():
    logic_(new CourseSide::Logic),
    city_(new Students::City),
    mainwindow_(new Students::MainWindow)
{
    logic_->fileConfig();
    logic_->takeCity(city_);
    logic_->finalizeGameStart();
    city_->setBackground(smallMap, bigMap);
}

void CreateGame::StartGame()
{
    mainwindow_->show();
    mainwindow_->setPicture(city_->getBackground());
    mainwindow_->drawStops(city_->getStops());
}
}
