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
    model = new QStringListModel(this);
    write_highscores();
    display_highscores();
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

bool gameover::compare(QPair<QString, int>& a, QPair<QString, int>& b)
{
    return a.second < b.second;
}

QMap<QString, int> gameover::sort_highscore(QMap<QString, int>& unsorted)
{
    QMap<int, QString> sort_map;
    QMap<QString, int>::iterator sort_iter = unsorted.begin();
    while(sort_iter!=unsorted.end()){
        sort_map[sort_iter.value()] = sort_iter.key();
        ++sort_iter;
    }
    QList<int> keys = sort_map.keys();
    std::sort(keys.begin(), keys.end());
    QMap<QString, int> sorted_higscores;
    for (auto score : keys) {
        sorted_higscores[sort_map[score]] = score;
    }
    return sorted_higscores;
}

void gameover::display_highscores()
{
    //Read score data to a map
    std::ifstream file("highscores.csv");
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row = split(line, ',');
        highscores_[QString::fromStdString(row.at(0))] = std::stoi(row.at(1));
    }

    QMap<QString, int> sorted_highscores = sort_highscore(highscores_);

    //Display score data stored in higscores map
    QMap<QString, int>::iterator iter = sorted_highscores.begin();
    while(iter!=sorted_highscores.end()){
        QString listItem = iter.key() + ": " + QString::number(iter.value());
        List << listItem;
        model->setStringList(List);
        ui->listView_highscores->setModel(model);
        ++iter;
    }
}


void gameover::write_highscores()
{
    std::fstream file;
    file.open("highscores.csv", std::ios_base::app);
    if (!file.is_open()) {
        qDebug() << "new file";
        std::ofstream file("highscores.csv");
        std::string name = stats_->get_score().first.toStdString();
        int score = stats_->get_score().second;
        file << name << ',' << score << "\n";
        file.close();
    }else if (file.is_open()){
        qDebug() << "file opened";
        std::string name = stats_->get_score().first.toStdString();
        int score = stats_->get_score().second;
        file << name << ',' << score << "\n";
        file.close();
    }
}
void Students::gameover::on_pushButton_quit_clicked()
{
    accept();
}


}

