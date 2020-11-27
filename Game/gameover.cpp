#include "gameover.h"
#include "ui_gameover.h"
#include "iostream"
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <sstream>

#include <QDebug>

namespace Students {

gameover::gameover(BetterMainWindow *parent) :
    QDialog(parent),
    ui(new Ui::gameover)
{
    ui->setupUi(this);
    stats_ = parent->get_stats();
    ui->lcdNumber_score->display(stats_->get_score().second);
    ui->lcdNumber_bombs->display(stats_->get_bombs_amount());
    model = new QStringListModel(this);
    QString diff = stats_->getDifficulty();
    filename_init_ = QString("highscores_%1.csv").arg(diff);
    qDebug()<<filename_init_;
    filename_ = filename_init_.toStdString();
    ui->label_highscore->setText(QString("Higscores for %1").arg(diff));



    write_highscores();

}

gameover::~gameover()
{
    delete ui;
}

std::vector<std::string> gameover::split(const std::string& s, const char delimiter, bool ignore_empty){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

QList<QPair<QString, int>> gameover::sort_highscore(QMap<QString, int>& unsorted)
{
    QList<QPair<QString, int>> pair_list;
    QMap<QString, int> sorted;
    QMap<QString, int>::iterator iter = unsorted.begin();
    while(iter!=unsorted.end()){
        pair_list.append(qMakePair(iter.key(), iter.value()));
        ++iter;
    }
    std::sort(pair_list.begin(), pair_list.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });
    return pair_list;
}

void gameover::display_highscores()
{
    std::ifstream file(filename_);
    std::string line;
    qDebug() << QString::fromStdString(filename_);
    while (std::getline(file, line)) {
        std::vector<std::string> row = split(line, ',');
        QString row_name = QString::fromStdString(row.at(0));
        int row_score = std::stoi(row.at(1));
        if ((highscores_.contains(row_name) && highscores_[row_name] < row_score) || !highscores_.contains(row_name)){
            highscores_[row_name] = row_score;
        }
    }

    QList<QPair<QString, int>> sorted_highscores = sort_highscore(highscores_);

    //Display score data stored in higscores map
    for (const auto &i : qAsConst(sorted_highscores)){
        QString listItem = i.first + ": " + QString::number(i.second);
        List << listItem;
        model->setStringList(List);
        ui->listView_highscores->setModel(model);
    }
}


void gameover::write_highscores()
{


    std::fstream file;
    file.open(filename_, std::ios_base::app);
    qDebug() << QString::fromStdString(filename_);

    if (!file.is_open()) {
        qDebug() << "new file";
        std::ofstream file(filename_);
        std::string name = stats_->get_score().first.toStdString();
        int score = stats_->get_score().second;
        file << name << ',' << score << "\n";
        file.close();
        highscores_[QString::fromStdString(name)] = score;
    }else if (file.is_open()){
        qDebug() << "file opened";
        QString name = stats_->get_score().first;

        //Write new score to file
        std::string input_name = name.toStdString();
        int score = stats_->get_score().second;
        file << input_name << ',' << score << "\n";
        file.close();
        }

        display_highscores();
    }
}
void Students::gameover::on_pushButton_quit_clicked()
{
    accept();
}




