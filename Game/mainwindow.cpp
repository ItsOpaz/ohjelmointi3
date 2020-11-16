#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics/simplemainwindow.hh"
#include "core/logic.hh"
#include "QImage"
#include "QDebug"
#include "QTime"
#include "QTimer"


namespace Students {

MainWindow::MainWindow(QWidget *parent) :
    SimpleMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    map = new QGraphicsScene(this);
    ui->gameWindow->setScene(map);
    map->setSceneRect(0,0,1095,592);
}

MainWindow::~MainWindow()
{
}

void MainWindow::drawStops(std::vector<std::shared_ptr<Interface::IStop> > stops)
{
    for (auto stop : stops){
        QGraphicsPixmapItem *stoppista = new QGraphicsPixmapItem(QString(":/graphics/graphics/passenger.svg"));
        int x = stop->getLocation().giveX();
        int y = 500 - stop->getLocation().giveY();
        stoppista->setScale(.05);
        stoppista->setPos(x,y);
        map->addItem(stoppista);
    }

}

void MainWindow::drawBusses( std::vector<std::shared_ptr<Interface::IActor> > actors)
{
    for (auto actor : actors){
        int saab = rand()%5 + 1;
        QGraphicsPixmapItem *stoppista = new QGraphicsPixmapItem(QString(":/graphics/graphics/saab1.svg"));
        int x = actor->giveLocation().giveX();
        int y = 500 - actor->giveLocation().giveY();
        stoppista->setScale(.05);
        stoppista->setPos(x,y);
        map->addItem(stoppista);
    }
}

void MainWindow::on_pushButton_menu_clicked()
{
    qDebug() << "menu clicked";
}

void MainWindow::update_clock()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    ui->lcdClock->display(text);

}

void MainWindow::setPicture(QImage img)
{
    map->setBackgroundBrush(img);
}
}
