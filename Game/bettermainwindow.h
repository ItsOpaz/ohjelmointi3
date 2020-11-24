#ifndef BETTERMAINWINDOW_H
#define BETTERMAINWINDOW_H

#include "betteractoritem.h"
#include "interfaces/iactor.hh"
#include "interfaces/istop.hh"
#include "character.h"
#include "bomb.h"
#include "plane.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>

const int X_ADJUST = 347;
const int Y_ADJUST = 552;

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

    void setSize(int, int);
    void setTick(int);

    void addActor(std::shared_ptr<Interface::IActor>);
    void addStop(std::shared_ptr<Interface::IStop>);
    void updateCoords(std::shared_ptr<Interface::IActor>);
    void setPicture(QImage &img);
    void addCharacter();
    void addPlane();
    void removeItem(std::shared_ptr<Interface::IActor>);
    bool checkActor(std::shared_ptr<Interface::IActor>);
    std::vector<std::shared_ptr<Interface::IActor>> getActors();

signals:
    void gameStarted();

public slots:
    void explosion(Bomb*);

private slots:
    void on_startButton_clicked();
    void keyPressEvent(QKeyEvent*);
    void set_playername(QString);
    void update();
    bool eventFilter(QObject *object, QEvent *event);

private:
    Ui::BetterMainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    QVector<std::pair<BetterActorItem*, std::shared_ptr<Interface::IActor>>> actorpairs_;
    QVector<std::pair<BetterActorItem*, std::shared_ptr<Interface::IStop>>> stoppairs_;
    QVector<Plane *> planes_;
    QString playerName_;
    Character* character_;
    QVector<Bomb *> bombs_;

    int width_ = 1095; //pxls
    int height_ = 592;
    int tick_ = 10; //ms
    int totalPoints_ =  0;
};

}

#endif // BETTERMAINWINDOW_H
