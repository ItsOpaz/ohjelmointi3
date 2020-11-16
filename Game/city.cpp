#include "city.h"
#include "mainwindow.h"
#include "QDebug"

namespace Students
{

City::City():
    Interface::ICity(){
}

void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    background_ = bigbackground;
}

void City::setClock(QTime clock)
{
    clock_ = clock;
}

void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    stops_.push_back(stop);

}

void City::startGame()
{

}

void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    actors_.push_back(newactor);
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    if (std::find(actors_.begin(), actors_.end(), actor)!=actors_.end()){
        actor->remove();
    }
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{

}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{

}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{

}

std::vector<std::shared_ptr<Interface::IActor> > City::getNearbyActors(Interface::Location loc) const
{

}

bool City::isGameOver() const
{
    return gameStatus_;
}

std::vector<std::shared_ptr<Interface::IActor> > City::getActors()
{
    return actors_;
}

std::vector<std::shared_ptr<Interface::IStop> > City::getStops()
{
    return stops_;
}

QImage City::getBackground()
{
    return background_;
}

QTime City::getTime()
{
    return clock_;
}
}





