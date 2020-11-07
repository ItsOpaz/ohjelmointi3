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

}

void City::setClock(QTime clock)
{

}

void City::addStop(std::shared_ptr<Interface::IStop> stop)
{

}

void City::startGame()
{

}

void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{

}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{

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
    return false;

}
}





