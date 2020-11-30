#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>

/**
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
    bool check_name(QString name);

private slots:
    //Handles typing player name
    void on_lineEdit_playername_textChanged(const QString &arg1);

    void on_pushButton_start_clicked();

    void on_radioButton_easy_clicked();

    void on_radioButton_medium_clicked();

    void on_radioButton_hard_clicked();

    void on_pushButton_cancel_clicked();

    void on_radioButton_instakill_clicked();

signals:
    //Sends current player info to mainwindow
    void infoSet(QString name, QString difficulty);


private:


    Ui::startwindow *ui;
    QString difficulty_ = NULL;
    QString playerName_ = "";

    //Illegal symbols in player name
    const std::vector<QChar> illegals_ = {',', '/', ' '};

};
}
#endif // STARTWINDOW_H
