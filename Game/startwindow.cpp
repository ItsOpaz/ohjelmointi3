#include "startwindow.h"
#include "ui_startwindow.h"
#include "QDebug"

namespace Students {


startwindow::startwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startwindow)
{
    ui->setupUi(this);
}

startwindow::~startwindow()
{
    delete ui;
}

void startwindow::setDifficulty(QString difficulty)
{
    difficulty_ = difficulty;
    qDebug() << difficulty_;
}

void startwindow::on_lineEdit_playername_textChanged(const QString &arg1)
{
    playerName_ = arg1;
    qDebug() << playerName_;
}
}

void Students::startwindow::on_pushButton_clicked()
{
    accept();
}

void Students::startwindow::on_radioButton_easy_clicked()
{
    setDifficulty("easy");
}

void Students::startwindow::on_radioButton_medium_clicked()
{
        setDifficulty("medium");
}

void Students::startwindow::on_radioButton_hard_clicked()
{
    setDifficulty("hard");
}
