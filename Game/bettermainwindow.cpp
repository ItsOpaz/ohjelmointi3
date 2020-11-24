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
    int x = it->second->giveLocation().giveX() + X_ADJUST;
    int y = Y_ADJUST - it->second->giveLocation().giveY();
    it->first->setCoord(x, y);
    std::shared_ptr<CourseSide::Nysse> bus = std::dynamic_pointer_cast<CourseSide::Nysse>(actor);
    it->first->setPoints(bus->getPassengers().size());
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
    QScrollBar* horizontal = ui->gameView->QAbstractScrollArea::horizontalScrollBar();
    QScrollBar* vertical = ui->gameView->QAbstractScrollArea::verticalScrollBar();
    connect(character_, SIGNAL(moveHorizontalScroll(int)), horizontal, SLOT(setValue(int)));
    connect(character_, SIGNAL(moveVerticalScroll(int)), vertical, SLOT(setValue(int)));
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
    int collisionPoints = 0;
    for(auto i : collisions){
        if(dynamic_cast<Character *>(i)){
            character_->crash(true);
        }else{
            BetterActorItem *item = dynamic_cast<BetterActorItem*>(i);
            collisionPoints += item->points();
        }
    }
    totalPoints_ += collisionPoints;
    qDebug()<<"siinä luikahti"<<collisionPoints<<"bongoo taskuun ja näin";
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
    //count of enemy planes is set here
    while(planes_.length() < 10){
        Plane *plane = new Plane();
        planes_.append(plane);
        map->addItem(plane);
    }
    //character is moved and character crash will be checked
    character_->move();
    character_->crash(false);
    //move enemyplanes
    for(auto plane : planes_){
        if(plane->checkPos()){
            plane->move();
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
            delete bomb;
        }
    }
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
