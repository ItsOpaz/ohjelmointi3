#ifndef BETTERMAINWINDOW_H
#define BETTERMAINWINDOW_H

#include "betteractoritem.h"
#include "interfaces/iactor.hh"
#include "interfaces/istop.hh"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>

namespace Ui {
class BetterMainWindow;
}

namespace Students {

class BetterMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BetterMainWindow(QWidget *parent = 0);
    virtual ~BetterMainWindow();

    void setSize(int w, int h);
    void setTick(int t);

    void addActor(int x, int y, int type);
    void addStop(std::shared_ptr<Interface::IStop>);
    void updateCoords(int distance, int x, int y);
    void setPicture(QImage &img);

signals:
    void gameStarted();

private slots:
    void on_startButton_clicked();
    void set_playername(QString name);

private:
    Ui::BetterMainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    QVector<BetterActorItem*> actors_;
    QString playerName_;

    int width_ = 1095; //pxls
    int height_ = 592;
    int tick_ = 500; //ms
};

}

#endif // BETTERMAINWINDOW_H
