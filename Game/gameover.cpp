#include "gameover.h"
#include "ui_gameover.h"

namespace Students {

gameover::gameover(BetterMainWindow *parent) :
    QDialog(parent),
    ui(new Ui::gameover)
{
    ui->setupUi(this);
    stats_ = parent->get_stats();
    ui->lcdNumber_score->display(stats_->get_score().second);
}

gameover::~gameover()
{
    delete ui;
}
void Students::gameover::on_pushButton_quit_clicked()
{
    accept();
}


}

