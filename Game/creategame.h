#ifndef CREATEGAME_H
#define CREATEGAME_H

#include "core/logic.hh"
#include "city.h"
#include "bettermainwindow.h"

namespace Students {

class CreateGame
{
public:
    CreateGame();
    void StartGame();
private:
    std::unique_ptr<CourseSide::Logic> logic_;
    std::shared_ptr<Students::City> city_;
    std::shared_ptr<Students::BetterMainWindow> mainwindow_;
};

}


#endif // CREATEGAME_H
