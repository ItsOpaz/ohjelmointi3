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

namespace Students {

BetterMainWindow::BetterMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BetterMainWindow),
    stats_(new statistics)
{
    Students::startwindow sw(this);
    connect(&sw, &startwindow::infoSet, this, &BetterMainWindow::set_stat_info);
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

void BetterMainWindow::game_over()
{
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
    for(auto i : collisions){
        if(dynamic_cast<Character *>(i)){
            character_->crash(true);
        }else if(dynamic_cast<Bomb *>(i)){
            break;
        }else if(dynamic_cast<Plane *>(i)){
            Plane *plane = dynamic_cast<Plane *>(i);
            if(plane->status()){
                plane->destroy();
                collisionPoints += 15;
                planes_.erase(std::remove(planes_.begin(), planes_.end(), plane), planes_.end());
            }
        }else{
            BetterActorItem *item = dynamic_cast<BetterActorItem *>(i);
            if(item->status()){
                item->destroy();
                collisionPoints += item->points();
            }
        }
    }
    stats_->increase_score(collisionPoints);
    ui->lcdNumber_score_display->display(stats_->get_score().second);
    qDebug()<<"siinä luikahti"<<collisionPoints<<"bongoo taskuun ja näin";
    qDebug()<<"tilastoja on tollai->"<<stats_->get_score();
}

void BetterMainWindow::set_stat_info(QString name, QString diff)
{
    stats_->set_info(name, diff);
}

void BetterMainWindow::damage_taken()
{
    ui->lcdNumber_lifes->display(stats_->get_lifes());
    switch (stats_->get_lifes()) {
    case 2:
        ui->lcdNumber_lifes->setPalette(Qt::yellow);
        break;
    case 1:
        ui->lcdNumber_lifes->setPalette(Qt::red);
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
            stats_->bomb_dropped();
            ui->lcdNumber_bombs_dropped->display(stats_->get_bombs_amount());
        }
        break;
        }
    case Qt::Key_Escape:{
        close();
    }
    default:

        break;
    }
}


void BetterMainWindow::update()
{
    ui->gameView->centerOn(character_);
    //count of enemy planes is set here
    while(planes_.length() < 10){
        addPlane();
    }
    //character is moved and character crash will be checked
    character_->move();
    character_->crash(false);
    //move enemyplanes
    for(auto plane : planes_){
        if(plane->checkPos()){
            plane->move();
            if(plane->collidesWithItem(character_)){
                //character_->crash(true);
            }
        }else{
            planes_.erase(std::remove(planes_.begin(), planes_.end(), plane), planes_.end());
            map->removeItem(plane);
        }
    }
    //active bombs will be ticked and inactive will be removed
    for (auto bomb : bombs_){
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
