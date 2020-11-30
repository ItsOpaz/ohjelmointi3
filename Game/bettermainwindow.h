#ifndef BETTERMAINWINDOW_H
#define BETTERMAINWINDOW_H

#include "betteractoritem.h"
#include "interfaces/iactor.hh"
#include "interfaces/istop.hh"
#include "character.h"
#include "bomb.h"
#include "plane.h"
#include "statistics.h"
#include "powerup.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>
#include <QSound>

const int X_ADJUST = 347;
const int Y_ADJUST = 540;

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
    /**
     * @brief sets ticks that timer will use
     * @param ticks
     */
    void setTick(int);
    /**
     * @brief adds actor to scene
     * @param actor to be added
     */
    void addActor(std::shared_ptr<Interface::IActor>);
    /**
     * @brief adds stop to scene
     * @param stop to be added
     */
    void addStop(std::shared_ptr<Interface::IStop>);
    /**
     * @brief updates graphicitems coordinates according to actor
     * @param actor to be moved
     */
    void updateCoords(std::shared_ptr<Interface::IActor>);
    /**
     * @brief sets background of scene
     * @param img to be set background
     */
    void setPicture(QImage &img);
    /**
     * @brief adds player character to scene
     */
    void addCharacter();
    /**
     * @brief adds enemyplanes to scene
     */
    void addPlane();
    /**
     * @brief adds bombable powerups to scene
     * @param type of powerup, 1 for apache upgrade, 2 for reseting planecount
     */
    void addPowerup(int);
    /**
     * @brief removes graphicitem related to actor
     * @param actor to be removed
     */
    void removeItem(std::shared_ptr<Interface::IActor>);
    /**
     * @brief checks if actor is in scene
     * @param actor to be checked
     * @return true if found, false if not
     */
    bool checkActor(std::shared_ptr<Interface::IActor>);
    /**
     * @brief returns actors
     * @return actors in scene
     */
    std::vector<std::shared_ptr<Interface::IActor>> getActors();
    /**
     * @brief ends game, shows gameover dialog and stops music
     */
    void game_over();
    /**
     * @brief returns statistics object
     * @return statistics object
     */
    statistics* get_stats();
    /**
     * @brief returns gameover status, called by city gameover function
     * @return
     */
    int getGameOver() const;

public slots:
    /**
     * @brief conncted to bombexplosion in bomb class
     * @param bomb object that explodes
     */
    void explosion(Bomb*);
    /**
     * @brief conneceted to startwindow info_set
     * @param name, difficulty
     */
    void set_difficulty(QString, QString);
    /**
     * @brief connected to crash in character class
     */
    void damage_taken();
    /**
     * @brief connected to remove plane in plane class
     * @param Plane that will be removed from scene
     */
    void planeRemoved(Plane *);

private slots:
    void keyPressEvent(QKeyEvent*);
    /**
     * @brief updates gameview, centers gameview to character, moves character, checks character collisions, increases planecount every 10 seconds
     */
    void update();
    /**
     * @brief filters out mouse wheel events so player cant scroll window so view moves with character
     * @param object
     * @param event
     * @return true or false for eventfilter
     */
    bool eventFilter(QObject *object, QEvent *event);

private:
    Ui::BetterMainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    QMap<std::shared_ptr<Interface::IActor>, BetterActorItem *> actorpairs_;
    QMap<std::shared_ptr<Interface::IStop>, BetterActorItem *> stoppairs_;
    Character* character_;
    statistics* stats_;

    int width_ = 1095; //pxls
    int height_ = 592; //pxls
    int tick_ = 10; //ms
    //tracks how many planes can be in view
    int planeCount;
    //tracks how many planes are in a view
    int planesActive_ = 0;
    //checks if bomb is dropped and not yet exploded
    bool bombActive_ = false;
    //sets bombradius for bombs
    double bombRadius;
    //true if gameends
    int gameOver_ = false;

};

}

#endif // BETTERMAINWINDOW_H
