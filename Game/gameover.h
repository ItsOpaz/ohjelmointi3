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

/**
  * @file
  * @brief Defines a class that handles the situation of game ending
  * Creates a dialog box that displays player score, amount of dropped bombs and local highscores for selected difficulty
  */


namespace Ui {
class gameover;
}

namespace Students {
class gameover : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Sets display widgets and selects correct higscore file
     * @param parent mainwindow
     */
    gameover(BetterMainWindow *parent);
    ~gameover();
    /**
     * @brief Tries to open a highscore file (.csv), if it does not exist, new one is generated. Writes current session's score to file.
     */
    void write_highscores();
    /**
     * @brief Saves current file's highscore data to a map and displays higscores in ListView widget
     */
    void display_highscores();
    /**
     * @brief splits string to vector on selected delimiter
     * @param s string to be split
     * @param delimiter char used for splitting
     * @param ignore_empty
     * @return vector of strings
     */
    std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false);

    /**
     * @brief saves QMap to a QList and sorts that list descending according to QPair second
     * @return sorted list of pairs
     */
    QList<QPair<QString, int> > sort_highscore(QMap<QString, int> &);

private slots:
    /**
     * @brief Exits program
     */
    void on_pushButton_quit_clicked();

private:
    Ui::gameover *ui;

    //Current sessions stats
    statistics* stats_;

    //Data structure for highscores, key is player name and value is score
    QMap<QString, int> highscores_;

    //Models for displaying highscores
    QStringListModel *model;
    QStringList List;

    //Helper for selecting filename
    QString filename_init_;

    std::string filename_;

};
}



#endif // GAMEOVER_H
