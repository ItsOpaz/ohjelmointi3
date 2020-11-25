#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>

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
    bool check_name(QString name);

private slots:
    void on_lineEdit_playername_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_radioButton_easy_clicked();

    void on_radioButton_medium_clicked();

    void on_radioButton_hard_clicked();

    void on_pushButton_cancel_clicked();

signals:
    void infoSet(QString name, QString difficulty);


private:


    Ui::startwindow *ui;
    QString difficulty_ = NULL;
    QString playerName_;
    std::vector<QChar> illegals_ = {',', '/', ' '};

};
}
#endif // STARTWINDOW_H
