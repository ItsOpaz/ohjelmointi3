#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include "statistics.h"
#include "bettermainwindow.h"
#include "QMap"
#include <QFile>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QPair>

namespace Ui {
class gameover;
}

namespace Students {
class gameover : public QDialog
{
    Q_OBJECT

public:
    gameover(BetterMainWindow *parent);
    ~gameover();
    void write_highscores();
    void display_highscores();
    std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false);
    bool compare(QPair<QString, int> &a,
                 QPair<QString, int> &b);
    QList<QPair<QString, int> > sort_highscore(QMap<QString, int> &);

private slots:
    void on_pushButton_quit_clicked();

private:
    Ui::gameover *ui;
    statistics* stats_;
    QMap<QString, int> highscores_;
    QStringListModel *model;
    QStringList List;
    QString filename_init_;
    std::string filename_;

    std::string EASY_FILE = "highscores_easy.csv";
    std::string MEDIUM_FILE = "highscores_medium.csv";
    std::string HARD_FILE = "highscores_hard.csv";
    std::string INSTAGIB_FILE = "highscores_instagib.csv";

};
}



#endif // GAMEOVER_H
