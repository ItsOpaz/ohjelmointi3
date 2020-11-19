#include "startwindow.h"
#include "ui_startwindow.h"
#include "QDebug"

namespace Students {


startwindow::startwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startwindow)
{
    ui->setupUi(this);
    ui->pushButton->setDisabled(true);
}

startwindow::~startwindow()
{
    delete ui;
}

void startwindow::setDifficulty(QString difficulty)
{
    difficulty_ = difficulty;
    ui->pushButton->setDisabled(false);
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
    emit nameSet(playerName_);
    emit difficultySet(difficulty_);
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
