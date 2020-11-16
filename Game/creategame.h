#ifndef CREATEGAME_H
#define CREATEGAME_H

#include "core/logic.hh"
#include "city.h"
#include "mainwindow.h"

namespace Students {

class CreateGame
{
public:
    CreateGame();
    void StartGame();
private:
    std::unique_ptr<CourseSide::Logic> logic_;
    std::shared_ptr<Interface::ICity> city_;
    std::unique_ptr<Students::MainWindow> mainwindow_;
};

}


#endif // CREATEGAME_H
