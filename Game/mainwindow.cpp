#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics/simplemainwindow.hh"

MainWindow::MainWindow(QWidget *parent) :
    SimpleMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

