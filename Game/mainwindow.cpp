#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics/simplemainwindow.hh"
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

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update_clock);
    timer->start(1000);
    update_clock();
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
}
}
