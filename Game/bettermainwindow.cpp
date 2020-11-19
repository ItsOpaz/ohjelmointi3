#include "bettermainwindow.h"
#include "ui_bettermainwindow.h"
#include <QDebug>
#include "startwindow.h"

const int PADDING = 10;

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

void BetterMainWindow::addActor(int x, int y, int type)
{
    BetterActorItem* nActor = new BetterActorItem(x, y, type);
    actors_.push_back(nActor);
    map->addItem(nActor);
}

void BetterMainWindow::addStop(std::shared_ptr<Interface::IStop> stop)
{
    QGraphicsPixmapItem *stoppista = new QGraphicsPixmapItem(QString(":/graphics/graphics/busstop.svg"));
    int x = stop->getLocation().giveX();
    int y = 500 - stop->getLocation().giveY();
    stoppista->setScale(.2);
    stoppista->setPos(x,y);
    map->addItem(stoppista);

}

void BetterMainWindow::updateCoords(int distance, int x, int y)
{
    actors_[distance]->setCoord(x,y);
}

void BetterMainWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
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
