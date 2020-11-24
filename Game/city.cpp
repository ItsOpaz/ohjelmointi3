#include "city.h"
#include "bettermainwindow.h"
#include "QDebug"
#include <typeinfo>
#include <iostream>
#include "character.h"

namespace Students
{

City::City():
    Interface::ICity(){
}

void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    mw_->setPicture(bigbackground);
}

void City::setClock(QTime clock)
{
    clock_ = clock;
}

void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    mw_->addStop(stop);
}

void City::startGame()
{
    mw_->addCharacter();
    mw_->showMaximized();
}

void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    mw_->addActor(newactor);
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    mw_->removeItem(actor);
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    mw_->removeItem(actor);
}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    return mw_->checkActor(actor);
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    mw_->updateCoords(actor);
}

std::vector<std::shared_ptr<Interface::IActor> > City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor>> nearby;
    auto allActors = mw_->getActors();
    for (auto actor : allActors){
        if(actor->giveLocation().isClose(loc)){
            nearby.push_back(actor);
        }
    }
    return nearby;
}

bool City::isGameOver() const
{
    return gameStatus_;
}

bool City::takeMainWindow(std::shared_ptr<Students::BetterMainWindow> mainwindow)
{
    mw_ = mainwindow;
    return true;
}
}





