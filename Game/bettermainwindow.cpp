#include "bettermainwindow.h"
#include "ui_bettermainwindow.h"
#include <QDebug>
#include "startwindow.h"
#include "character.h"
#include "actors/nysse.hh"
#include "creategame.h"
#include <QKeyEvent>
#include "core/location.hh"
#include <QDesktopWidget>
#include <QScreen>
#include <QScrollBar>
#include "plane.h"
#include "gameover.h"
#include "powerup.h"

QSound THEME(":/sounds/sounds/helicopter.wav");
QSound WRONG(":/sounds/sounds/aah.wav");

namespace Students {

BetterMainWindow::BetterMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BetterMainWindow),
    stats_(new statistics)
{
    Students::startwindow sw(this);
    connect(&sw, &startwindow::infoSet, this, &BetterMainWindow::set_difficulty);
    if (sw.exec()) {
        ui->setupUi(this);
        map = new QGraphicsScene(this);
        map->setSceneRect(0,0,width_,height_);
        ui->gameView->setScene(map);
        //gameview is set to screensize
        QRect  sGeometry = QGuiApplication::primaryScreen()->geometry();
        ui->gameView->resize(sGeometry.width(), sGeometry.height());
        //ScrollBars are hidden
        ui->gameView->QAbstractScrollArea::setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
        ui->gameView->QAbstractScrollArea::setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
        //set mousewheel event filter for gameview
        ui->gameView->viewport()->installEventFilter(this);
        ui->gameView->scale(4, 4);
        //set player name display and starting lifes amount
        ui->label_player_name->setText(stats_->get_score().first);
        ui->lcdNumber_lifes->display(stats_->get_lifes());
        ui->lcdNumber_lifes->setPalette(Qt::green);

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &BetterMainWindow::update);
        timer->start(tick_);
        THEME.setLoops(QSound::Infinite);
        THEME.play();
        addPowerup(1);
        if(stats_->getDifficulty() == "easy"){
            addPowerup(2);
            addPowerup(2);
        }else if(stats_->getDifficulty() == "medium"){
            addPowerup(2);
        }
    }
    else{
        qApp->quit();
    }
}

BetterMainWindow::~BetterMainWindow()
{
    delete ui;
    delete character_;
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
    int x = newActor->giveLocation().giveX() + X_ADJUST;
    int y = Y_ADJUST - newActor->giveLocation().giveY();
    BetterActorItem* nActor = new BetterActorItem(x, y, 0, false);
    actorpairs_.insert(newActor, nActor);
    map->addItem(nActor);
}

void BetterMainWindow::addStop(std::shared_ptr<Interface::IStop> stop)
{
    int x = stop->getLocation().giveX() + X_ADJUST;
    int y = Y_ADJUST - stop->getLocation().giveY();
    BetterActorItem* nStop = new BetterActorItem(x, y, 1, true);
    stoppairs_.insert(stop, nStop);
    map->addItem(nStop);
}



void BetterMainWindow::updateCoords(std::shared_ptr<Interface::IActor> actor)
{
    if(actorpairs_[actor]->status()){
        int x = actor->giveLocation().giveX() + X_ADJUST;
        int y = Y_ADJUST - actor->giveLocation().giveY();
        actorpairs_[actor]->setCoord(x,y);
        std::shared_ptr<CourseSide::Nysse> bus = std::dynamic_pointer_cast<CourseSide::Nysse>(actor);
        actorpairs_[actor]->setPoints(bus->getPassengers().size());
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
    ui->gameView->centerOn(character_);
    connect(character_, &Character::damage_recieved, this, &BetterMainWindow::damage_taken);
}

void BetterMainWindow::addPlane()
{
    Plane *plane = new Plane();
    connect(timer, &QTimer::timeout, plane, &Plane::move);
    connect(plane, &Plane::removePlane, this, &BetterMainWindow::planeRemoved);
    ++planesActive_;
    map->addItem(plane);
}

void BetterMainWindow::planeRemoved(Plane *plane)
{
    map->removeItem(plane);
    delete plane;
    --planesActive_;
}

void BetterMainWindow::addPowerup(int value)
{
    Powerup *powerup = new Powerup(value);
    map->addItem(powerup);
}


void BetterMainWindow::removeItem(std::shared_ptr<Interface::IActor> actor)
{
    actorpairs_.remove(actor);
}

bool BetterMainWindow::checkActor(std::shared_ptr<Interface::IActor> actor)
{
    if(actorpairs_.find(actor) == actorpairs_.end()){
        return false;
    }else{
        return true;
    }

}

std::vector<std::shared_ptr<Interface::IActor> > BetterMainWindow::getActors()
{
    std::vector<std::shared_ptr<Interface::IActor> > actors;
    for (auto actor : actorpairs_.keys()){
        actors.push_back(actor);
    }
    return actors;
}

void BetterMainWindow::game_over()
{
    THEME.stop();
    gameOver_ = true;
    QSound::play(":/sounds/sounds/ei_onnistu.wav");
    Students::gameover end_window(this);
    end_window.exec();
    close();
}

statistics *BetterMainWindow::get_stats()
{
    return stats_;
}

void BetterMainWindow::explosion(Bomb *bomb)
{
    bombActive_ = false;
    auto collisions = bomb->collidingItems();
    int collisionPoints = 0;
    for(auto i : qAsConst(collisions)){
        if(auto item = dynamic_cast<BetterActorItem *>(i)){
            if(item != nullptr && item->status()){
                item->destroy();
                collisionPoints += item->points();
            }
        }else if(auto plane = dynamic_cast<Plane *>(i)){
            if(plane->status()){
                plane->destroy();
                collisionPoints += 15;
                --planesActive_;
            }
        }else if(auto powerup = dynamic_cast<Powerup *>(i)){
            if(powerup->getType() == 1){
                character_->transfrom();
            }else{
                planeCount = 0;
            }
            map->removeItem(i);
        }else if(dynamic_cast<Character *>(i)){
            character_->crash();
        }
    }
    if(collisionPoints == 0){
        QSound::play(":/sounds/sounds/nollanollanolla.wav");
    }else if(collisionPoints < 3){
        QSound::play(":/sounds/sounds/nolla.wav");
    }else if(collisionPoints < 6){
        QSound::play(":/sounds/sounds/yks.wav");
    }else if(collisionPoints < 9){
        QSound::play(":/sounds/sounds/kaksi.wav");
    }else if(collisionPoints < 12){
        QSound::play(":/sounds/sounds/kolme.wav");
    }else if(collisionPoints < 15){
        QSound::play(":/sounds/sounds/nelja.wav");
    }else{
        QSound::play(":/sounds/sounds/viis.wav");
    }
    stats_->increase_score(collisionPoints);
    ui->lcdNumber_score_display->display(stats_->get_score().second);
}

void BetterMainWindow::set_difficulty(QString name, QString diff)
{
    if(diff == "easy"){
        planeCount = 5;
        bombRadius = .1;
    }else if(diff == "medium"){
        planeCount = 10;
        bombRadius = .07;
    }else if(diff == "hard"){
        planeCount = 15;
        bombRadius = .05;
    }else if(diff == "instakill"){
        planeCount = 15;
        bombRadius = .05;
        stats_->set_lifes(1);
    }
    stats_->set_info(name, diff);
}

void BetterMainWindow::damage_taken()
{
    stats_->reduce_lifes();
    ui->lcdNumber_lifes->display(stats_->get_lifes());
    switch (stats_->get_lifes()) {
    case 2:
        ui->lcdNumber_lifes->setPalette(Qt::yellow);
        QSound::play(":/sounds/sounds/wou.wav");
        break;
    case 1:
        ui->lcdNumber_lifes->setPalette(Qt::red);
        QSound::play(":/sounds/sounds/noni.wav");
        break;
    case 0:
        game_over();
        break;
    default:
        break;
    }
}


void BetterMainWindow::keyPressEvent(QKeyEvent *event)
{
    //character is given direction and rotation for every correct keyevent
    //dir 1(W) = North, 2(S) = South, 3(D) = East, (A)4 = West
    int dir = character_->direction();
    switch (event->key()) {
    case Qt::Key_W:
        if(dir != 2 || character_->getType() == 2){
            character_->setDirection(1);
            character_->setRotation(0);
        }
        break;
    case Qt::Key_S:
        if(dir != 1 || character_->getType() == 2){
            character_->setDirection(2);
            character_->setRotation(180);
        }
        break;
    case Qt::Key_A:
        if(dir != 3 || character_->getType() == 2){
            character_->setDirection(4);
            character_->setRotation(270);
        }
        break;
    case Qt::Key_D:
        if(dir != 4 || character_->getType() == 2){
            character_->setDirection(3);
            character_->setRotation(90);
        }
        break;
    //space key drops bomb if possible
    case Qt::Key_Space:{
        //if bomb is active, no more bombs can be dropped
        if(!bombActive_){
            QSound::play(":/sounds/sounds/jysahti.wav");
            //bomb is created in character class, character will give bomb rotation and position
            auto bomb = character_->dropBomb();
            bomb->setRadius(bombRadius);
            map->addItem(bomb);
            //timer is connected to bomb tick
            connect(timer, &QTimer::timeout, bomb, &Bomb::tick);
            connect(bomb, SIGNAL(bombExplosion(Bomb*)), this, SLOT(explosion(Bomb*)));
            stats_->bomb_dropped();
            ui->lcdNumber_bombs_dropped->display(stats_->get_bombs_amount());
            bombActive_ = true;
        }
        break;
        }
    //esc closes mainwindow
    case Qt::Key_Escape:{
        close();
        break;
    }
    default:
        //if wrong button is pressed, sound will be played
        if(WRONG.isFinished()){
            WRONG.play();
        }
        break;
    }
}


void BetterMainWindow::update()
{
    //gameview is centered on player so map moves with player
    ui->gameView->centerOn(character_);
    //every 10 seconds planecount is increased
    if(stats_->get_time() % 500 == 0 && stats_->get_time() != 0){
        ++planeCount;
    }
    //planes will be added if not enough planes are in play
    while(planesActive_ < planeCount){
        addPlane();
    }
    //character is moved and character crash will be checked
    character_->move();
    character_->wallhit();
    //collisions with enemy planes will be checked
    if(!character_->collidingItems().empty()){
        for(auto item : character_->collidingItems()){
            if(auto plane = dynamic_cast<Plane *>(item)){
                if(plane->status()){
                    plane->destroy();
                    character_->crash();
                    --planesActive_;
                }
            }
        }
    }
    stats_->tick_counter();
}

bool BetterMainWindow::eventFilter(QObject *object, QEvent *event)
{
    //filter out mousewheel events in gameview
    if (object == ui->gameView->viewport() && event->type() == QEvent::Wheel) {
        return true;
    }
    return false;
}

int BetterMainWindow::getGameOver() const
{
    return gameOver_;
}

}
