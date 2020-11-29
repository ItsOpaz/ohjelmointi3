#include "city.h"
#include "bettermainwindow.h"
#include "QDebug"
#include <typeinfo>
#include <iostream>
#include "character.h"
#include "actors/nysse.hh"


QImage bigbackground = QImage(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
QImage basicbackground = QImage(":/offlinedata/offlinedata/kartta_pieni_500x500.png");


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
    if(std::dynamic_pointer_cast<CourseSide::Nysse>(newactor) != nullptr){
        mw_->addActor(newactor);
    }
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    if(findActor(actor)){
        mw_->removeItem(actor);
    }
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    if(findActor(actor)){
        mw_->removeItem(actor);
    }
}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    return mw_->checkActor(actor);
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    if(findActor(actor)){
        mw_->updateCoords(actor);
    }
}

std::vector<std::shared_ptr<Interface::IActor> > City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor>> nearby;
    auto allActors = mw_->getActors();
    for (const auto &actor : allActors){
        if(actor->giveLocation().isClose(loc)){
            nearby.push_back(actor);
        }
    }
    return nearby;
}

bool City::isGameOver() const
{
    return mw_->getGameOver();
}

bool City::takeMainWindow(std::shared_ptr<Students::BetterMainWindow> mainwindow)
{
    mw_ = mainwindow;
    return true;
}
}
