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
    ui->label_errortext->hide();
}

startwindow::~startwindow()
{
    delete ui;
}

void startwindow::setDifficulty(QString difficulty)
{
    difficulty_ = difficulty;
    if (!check_name(playerName_)){
        ui->pushButton->setDisabled(true);
    }
    else{
        ui->pushButton->setDisabled(false);
    }
}

bool startwindow::check_name(QString name)
{
    if (name.isEmpty()){
        return false;
    }
    for (auto i: illegals_){
        if (name.contains(i)){
            return false;
        }
    }
    return true;
}

void startwindow::on_lineEdit_playername_textChanged(const QString &arg1)
{
    playerName_ = arg1;
    if (check_name(playerName_) && difficulty_!=NULL){
        ui->label_errortext->hide();
        ui->pushButton->setDisabled(false);
    }
    else if (!check_name(playerName_)){
        ui->label_errortext->show();
        ui->pushButton->setDisabled(true);
    }
}
}

void Students::startwindow::on_pushButton_clicked()
{
    emit infoSet(playerName_, difficulty_);
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

void Students::startwindow::on_pushButton_cancel_clicked()
{
    reject();
}

void Students::startwindow::on_radioButton_instakill_clicked()
{
    setDifficulty("instakill");
}
