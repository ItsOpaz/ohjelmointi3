#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include "bomb.h"
#include <QObject>

namespace Students {
class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Character();
    void move();
    int direction() const;
    void setDirection(int);
    void crash(bool);
    void rotorPhase();
    Bomb* dropBomb();
    void planeHit(bool);

signals:
    void damage_recieved();

private:
    int direction_;
    int phase_ = 1;
    bool planeHit_ = false;
};
}


#endif // CHARACTER_H
