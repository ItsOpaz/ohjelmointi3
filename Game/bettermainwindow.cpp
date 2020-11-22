#include "bettermainwindow.h"
#include "ui_bettermainwindow.h"
#include <QDebug>
#include "startwindow.h"
#include "character.h"
#include "actors/nysse.hh"

namespace Students {

BetterMainWindow::BetterMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BetterMainWindow)
{

    Students::startwindow sw(this);
    connect(&sw, &startwindow::nameSet, this, &BetterMainWindow::set_playername);

    ui->setupUi(this);
    ui->gameView->setFixedSize(width_, height_);
    ui->centralwidget->setFixedSize(width_ + ui->startButton->width() + PADDING, height_ + PADDING);

    ui->startButton->move(width_ + PADDING , PADDING);

    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0,width_,height_);

    resize(minimumSizeHint());
    //ui->gameView->fitInView(0,0, MAPWIDTH, MAPHEIGHT, Qt::KeepAspectRatio);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, map, &QGraphicsScene::advance);
    timer->start(tick_);
    sw.exec();

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
    Character* player = new Character(100, 100, 2);
    map->addItem(player);
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


void BetterMainWindow::on_startButton_clicked()
{
    qDebug() << "Start clicked";
    emit gameStarted();
}

void BetterMainWindow::set_playername(QString name)
{
    playerName_ = name;
    qDebug() << playerName_;
}
}
