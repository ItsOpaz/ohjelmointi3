#include "creategame.h"

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
}

void CreateGame::StartGame()
{
    mainwindow_->show();
    QImage bigMap = QImage(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    mainwindow_->setPicture(bigMap);
}
}
