#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics/simplemainwindow.hh"
#include "QImage"
#include "QDebug"


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
    delete ui;
}

void MainWindow::on_pushButton_menu_clicked()
{
    qDebug() << "menu clicked";
}

void MainWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
}
}
