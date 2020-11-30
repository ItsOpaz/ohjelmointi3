#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>

/**
 *@file
 * @brief Defines a start dialog window
 * Player can define player name and select difficulty, game cannot be started if name contains illegal symbols or difficulty is not set
 */

namespace Ui {
class startwindow;
}

namespace Students {


class startwindow : public QDialog
{
    Q_OBJECT

public:
    explicit startwindow(QWidget *parent = nullptr);
    ~startwindow();


    void setDifficulty (QString difficulty);
    /**
     * @brief checks if playername contains illegal chars
     * @param name players name
     * @return bool
     */
    /**
     * @brief check_name checks if player name is legal after every new character
     * @param current player name
     * @return bool
     */
    bool check_name(QString name);

    void reject();
private slots:
    //Handles typing player name
    void on_lineEdit_playername_textChanged(const QString &arg1);
    //Starts game and sends player info to mainwindow
    void on_pushButton_start_clicked();
    //Buttons for selecting difficulty
    void on_radioButton_easy_clicked();
    void on_radioButton_medium_clicked();
    void on_radioButton_hard_clicked();
    void on_radioButton_instakill_clicked();

signals:
    //Sends current player info to mainwindow
    void infoSet(QString name, QString difficulty);


private:
    Ui::startwindow *ui;
    QString difficulty_ = NULL;
    QString playerName_ = "";
    Qt::WindowFlags flags;

    //Illegal symbols in player name
    const std::vector<QChar> illegals_ = {',', '/', ' '};

};
}
#endif // STARTWINDOW_H
