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
        close();
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
    actorpairs_.push_back(std::make_pair(nActor, newActor));
    map->addItem(nActor);
}

void BetterMainWindow::addStop(std::shared_ptr<Interface::IStop> stop)
{
    int x = stop->getLocation().giveX() + X_ADJUST;
    int y = Y_ADJUST - stop->getLocation().giveY();
    BetterActorItem* nStop = new BetterActorItem(x, y, 1, true);
    stoppairs_.push_back(std::make_pair(nStop, stop));
    map->addItem(nStop);
}



void BetterMainWindow::updateCoords(std::shared_ptr<Interface::IActor> actor)
{
    auto it = std::find_if(actorpairs_.begin(), actorpairs_.end(), [&actor](const std::pair<BetterActorItem*, std::shared_ptr<Interface::IActor>>& element){ return element.second == actor;});
    if(it->first->status()){
        int x = it->second->giveLocation().giveX() + X_ADJUST;
        int y = Y_ADJUST - it->second->giveLocation().giveY();
        it->first->setCoord(x, y);
        std::shared_ptr<CourseSide::Nysse> bus = std::dynamic_pointer_cast<CourseSide::Nysse>(actor);
        it->first->setPoints(bus->getPassengers().size());
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
    connect(character_, &Character::damage_recieved, stats_, &statistics::reduce_lifes);
    connect(character_, &Character::damage_recieved, this, &BetterMainWindow::damage_taken);
}

void BetterMainWindow::addPlane()
{
    Plane *plane = new Plane();
    planes_.append(plane);
    map->addItem(plane);
}

void BetterMainWindow::addPowerup(int value)
{
    Powerup *powerup = new Powerup(value);
    //powerups_.append(powerup);
    map->addItem(powerup);
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
    for(const auto &item : qAsConst(actorpairs_)){
        actors.push_back(item.second);
    }
    return actors;
}

void BetterMainWindow::game_over()
{
    THEME.stop();
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
    //tähän settii mite pisteet lasketaa osumista
    //collisions vektori palauttaa kaikki grafiikkaitemit joihin pommi osuu
    //dynamic_pointer_cast varmaa loistava ratkasu, jolla saa myös nysse luokan methodit käyttöön (getPassengers)
    //pisteiden kannalta
    auto collisions = bomb->collidingItems();
    int collisionPoints = 0;
    for(auto i : qAsConst(collisions)){
        if(dynamic_cast<Character *>(i)){
            character_->crash();
        }else if(dynamic_cast<Bomb *>(i)){
            break;
        }else if(dynamic_cast<Plane *>(i)){
            Plane *plane = dynamic_cast<Plane *>(i);
            if(plane->status()){
                plane->destroy();
                collisionPoints += 15;
                planes_.erase(std::remove(planes_.begin(), planes_.end(), plane), planes_.end());
            }
        }else if(dynamic_cast<Powerup *>(i)){
            Powerup *powerup = dynamic_cast<Powerup *>(i);
            if(powerup->getType() == 1){
                character_->transfrom();
            }else{
                planeCount = 0;
            }
            map->removeItem(i);

        }else{
            BetterActorItem *item = dynamic_cast<BetterActorItem *>(i);
            if(item != nullptr && item->status()){
                item->destroy();
                collisionPoints += item->points();
            }
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
    //dir 1 = North, 2 = South, 3 = East, 4 = West
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
    case Qt::Key_Space:{
        //player is limited to 1 simultaneous bombs on the ground
        if(bombs_.size() < 1){
            QSound::play(":/sounds/sounds/jysahti.wav");
            auto bomb = character_->dropBomb();
            bomb->setRadius(bombRadius);
            map->addItem(bomb);
            bombs_.append(bomb);
            connect(bomb, SIGNAL(bombExplosion(Bomb*)), this, SLOT(explosion(Bomb*)));
            stats_->bomb_dropped();
            ui->lcdNumber_bombs_dropped->display(stats_->get_bombs_amount());
        }
        break;
        }
    case Qt::Key_Escape:{
        close();
    }
    default:
        QSound::play(":/sounds/sounds/aah.wav");
        break;
    }
}


void BetterMainWindow::update()
{
    //gameview is centered on player so map moves with player
    ui->gameView->centerOn(character_);
    //every 10 seconds planecount is increased
    if(stats_->get_time() % 1000 == 0 && stats_->get_time() != 0){
        planeCount ++;
    }
    //planes will be added if not enough planes are in play
    while(planes_.length() < planeCount){
        addPlane();
    }
    //character is moved and character crash will be checked
    character_->move();
    character_->wallhit();
    character_->planeHit(false);
    //move enemyplanes
    for(auto plane : qAsConst(planes_)){
        if(plane->checkPos()){
            plane->move();
            if(plane->collidesWithItem(character_)){
                plane->destroy();
                planes_.erase(std::remove(planes_.begin(), planes_.end(), plane), planes_.end());
                character_->planeHit(true);
            }
        }else{
            planes_.erase(std::remove(planes_.begin(), planes_.end(), plane), planes_.end());
            map->removeItem(plane);
        }
    }
    //active bombs will be ticked and inactive will be removed
    for (auto bomb : qAsConst(bombs_)){
        if(bomb->status()){
            bomb->tick();
        }else{
            bombs_.erase(std::remove(bombs_.begin(), bombs_.end(), bomb), bombs_.end());
            map->removeItem(bomb);
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

}
