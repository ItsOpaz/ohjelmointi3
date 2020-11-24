#include "bettermainwindow.h"
#include "ui_bettermainwindow.h"
#include <QDebug>
#include "startwindow.h"
#include "character.h"
#include "actors/nysse.hh"
#include "creategame.h"
#include <QKeyEvent>
#include "core/location.hh"

namespace Students {

BetterMainWindow::BetterMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BetterMainWindow)
{
    Students::startwindow sw(this);
    if (sw.exec()) {
        connect(&sw, &startwindow::nameSet, this, &BetterMainWindow::set_playername);

        ui->setupUi(this);
        map = new QGraphicsScene(this);
        ui->gameView->setScene(map);
        map->setSceneRect(0,0,width_,height_);

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &BetterMainWindow::update);
        timer->start(tick_);
    }
    else{
        close();
    }



}

BetterMainWindow::~BetterMainWindow()
{
    delete ui;
}

void BetterMainWindow::setSize(int w, int h)
{
    width_ = w;
    height_ = h;
}

void BetterMainWindow::setTick(int t)
{
    tick_ = t;
}

void BetterMainWindow::addActor(std::shared_ptr<Interface::IActor> newActor)
{
    int type = 0;
    if(std::dynamic_pointer_cast<CourseSide::Nysse>(newActor) == nullptr){
        type = 1;
    }
    int x = newActor->giveLocation().giveX() + X_ADJUST;
    int y = Y_ADJUST - newActor->giveLocation().giveY();

    BetterActorItem* nActor = new BetterActorItem(x, y, type);
    actorpairs_.push_back(std::make_pair(nActor, newActor));
    map->addItem(nActor);
}

void BetterMainWindow::addStop(std::shared_ptr<Interface::IStop> stop)
{
    QGraphicsPixmapItem *stoppista = new QGraphicsPixmapItem(QString(":/graphics/graphics/busstop.svg"));
    int x = stop->getLocation().giveX() + X_ADJUST;
    int y = Y_ADJUST - stop->getLocation().giveY();
    stoppista->setScale(.2);
    stoppista->setPos(x,y);
    map->addItem(stoppista);
}



void BetterMainWindow::updateCoords(std::shared_ptr<Interface::IActor> actor)
{
    auto it = std::find_if(actorpairs_.begin(), actorpairs_.end(), [&actor](const std::pair<BetterActorItem*, std::shared_ptr<Interface::IActor>>& element){ return element.second == actor;});
    int x = it->second->giveLocation().giveX() + X_ADJUST;
    int y = Y_ADJUST - it->second->giveLocation().giveY();
    it->first->setCoord(x, y);
    if(std::dynamic_pointer_cast<CourseSide::Passenger>(actor)){
        std::shared_ptr<CourseSide::Passenger> passenger = std::dynamic_pointer_cast<CourseSide::Passenger>(actor);
        if(passenger->isInVehicle()){
            it->first->hide();
        }else{
            it->first->show();
        }
    }
}

void BetterMainWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
}

void BetterMainWindow::addCharacter()
{
    character_ = new Character();
    map->addItem(character_);
}

void BetterMainWindow::removeItem(std::shared_ptr<Interface::IActor> actor)
{
    auto it = std::find_if(actorpairs_.begin(), actorpairs_.end(), [&actor](const std::pair<BetterActorItem*, std::shared_ptr<Interface::IActor>>& element){ return element.second == actor;});
    it->second->remove();
    map->removeItem(it->first);
    actorpairs_.erase(it);
}

bool BetterMainWindow::checkActor(std::shared_ptr<Interface::IActor> actor)
{
    return (std::find_if(actorpairs_.begin(), actorpairs_.end(), [&actor](const std::pair<BetterActorItem*, std::shared_ptr<Interface::IActor>>& element){ return element.second == actor;}) != actorpairs_.end());
}

std::vector<std::shared_ptr<Interface::IActor> > BetterMainWindow::getActors()
{
    std::vector<std::shared_ptr<Interface::IActor>> actors;
    for(auto item : actorpairs_){
        actors.push_back(item.second);
    }
    return actors;
}

void BetterMainWindow::explosion(Bomb *bomb)
{
    //tähän settii mite pisteet lasketaa osumista
    //collisions vektori palauttaa kaikki grafiikkaitemit joihin pommi osuu
    //dynamic_pointer_cast varmaa loistava ratkasu, jolla saa myös nysse luokan methodit käyttöön (getPassengers)
    //pisteiden kannalta
    auto collisions = bomb->collidingItems();
    qDebug()<<"siinä luikahti"<<collisions.length()<<"kohdetta pillun päreiks ja näin";
}


void BetterMainWindow::on_startButton_clicked()
{
    qDebug() << "Pause clicked";
    timer->stop();
}

void BetterMainWindow::keyPressEvent(QKeyEvent *event)
{
    //dir 1 = North, 2 = South, 3 = East, 4 = West
    int dir = character_->direction();
    switch (event->key()) {
    case Qt::Key_W:
        if(dir != 2){
            character_->setDirection(1);
        }
        break;
    case Qt::Key_S:
        if(dir != 1){
            character_->setDirection(2);
        }
        break;
    case Qt::Key_A:
        if(dir != 3){
            character_->setDirection(4);
        }
        break;
    case Qt::Key_D:
        if(dir != 4){
            character_->setDirection(3);
        }
        break;
    case Qt::Key_Space:{
        //player is limited to 3 simultaneous bombs on the ground
        if(bombs_.size() < 3){
            auto bomb = character_->dropBomb();
            map->addItem(bomb);
            bombs_.append(bomb);
            connect(bomb, SIGNAL(bombExplosion(Bomb*)), this, SLOT(explosion(Bomb*)));
        }
        break;
        }
    default:

        break;
    }
}

void BetterMainWindow::set_playername(QString name)
{
    playerName_ = name;
    qDebug() << playerName_;
}

void BetterMainWindow::update()
{
    //character is moved and character crash will be checked
    character_->move();
    character_->crash();
    //active bombs will be ticked and inactive will be removed
    for (auto bomb : bombs_){
        if(bomb->status()){
            bomb->tick();
        }else{
            bombs_.erase(std::remove(bombs_.begin(), bombs_.end(), bomb), bombs_.end());
            delete bomb;
        }
    }
}
}
