#ifndef CITY_H
#define CITY_H

#include "interfaces/icity.hh"
#include "bettermainwindow.h"

#include <QTime>

namespace Students {

class City : public Interface::ICity
{
public:
    City();

    // ICity interface
public:
    void setBackground(QImage &basicbackground, QImage &bigbackground);
    void setClock(QTime clock);
    void addStop(std::shared_ptr<Interface::IStop> stop);
    void startGame();
    void addActor(std::shared_ptr<Interface::IActor> newactor);
    void removeActor(std::shared_ptr<Interface::IActor> actor);
    void actorRemoved(std::shared_ptr<Interface::IActor> actor);
    bool findActor(std::shared_ptr<Interface::IActor> actor) const;
    void actorMoved(std::shared_ptr<Interface::IActor> actor);
    std::vector<std::shared_ptr<Interface::IActor> > getNearbyActors(Interface::Location loc) const;
    bool isGameOver() const;
    bool takeMainWindow(std::shared_ptr<Students::BetterMainWindow>);

private:
    QTime clock_;
    QImage background_;
    std::shared_ptr<Students::BetterMainWindow> mw_;
};
}

#endif // CITY_H
