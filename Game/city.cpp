#include "city.h"
#include "bettermainwindow.h"
#include "QDebug"
#include <typeinfo>
#include "actors/nysse.hh"
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
    stops_.push_back(stop);
    mw_->addStop(stop);
}

void City::startGame()
{
    mw_->addCharacter();
    mw_->show();
}

void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    int type = 0;
    if(std::dynamic_pointer_cast<CourseSide::Nysse>(newactor) == nullptr){
        type = 1;
    }
    int x = newactor->giveLocation().giveX() + X_ADJUST;
    int y = Y_ADJUST - newactor->giveLocation().giveY();
    mw_->addActor(x, y, type);
    actors_.push_back(newactor);
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
//    std::remove(actors_.begin(), actors_.end(), actor);
//    actor->remove();
//    std::vector<std::shared_ptr<Interface::IActor>>::iterator it = std::find(actors_.begin(), actors_.end(), actor);
//    mw_->removeItem(std::distance(actors_.begin(), it));
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{

}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{

}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    if(actor->isRemoved()){
        removeActor(actor);
    }else{
    int x = actor->giveLocation().giveX() + X_ADJUST;
    int y = Y_ADJUST - actor->giveLocation().giveY();
    std::vector<std::shared_ptr<Interface::IActor>>::iterator it = std::find(actors_.begin(), actors_.end(), actor);
    mw_->updateCoords(std::distance(actors_.begin(), it), x, y);
    }
}

std::vector<std::shared_ptr<Interface::IActor> > City::getNearbyActors(Interface::Location loc) const
{

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





