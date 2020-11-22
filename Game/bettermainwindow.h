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

//for big map X_ADJUST 353 and Y_ADJUST 444
//for small map X_ADJUST 0 and Y_ADJUST 500
const int X_ADJUST = 353;
const int Y_ADJUST = 444;

const int PADDING = 10;


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

    void addActor(std::shared_ptr<Interface::IActor>);
    void addStop(std::shared_ptr<Interface::IStop>);
    void updateCoords(std::shared_ptr<Interface::IActor>);
    void setPicture(QImage &img);
    void addCharacter();
    void removeItem(std::shared_ptr<Interface::IActor>);
    bool checkActor(std::shared_ptr<Interface::IActor>);
    std::vector<std::shared_ptr<Interface::IActor>> getActors();

signals:
    void gameStarted();

private slots:
    void on_startButton_clicked();
    void set_playername(QString name);

private:
    Ui::BetterMainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    QVector<std::pair<BetterActorItem*, std::shared_ptr<Interface::IActor>>> actorpairs_;
    QString playerName_;

    int width_ = 1095; //pxls
    int height_ = 592;
    int tick_ = 500; //ms
};

}

#endif // BETTERMAINWINDOW_H
