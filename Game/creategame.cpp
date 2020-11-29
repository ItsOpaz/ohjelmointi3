#include "creategame.h"

namespace Students
{
CreateGame::CreateGame():
    //creates city, logic and mainwindow for game
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
