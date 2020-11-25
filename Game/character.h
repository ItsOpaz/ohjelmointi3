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
    void crash();
    void rotorPhase();
    Bomb* dropBomb();
    void planeHit(bool);
    void wallhit();

signals:
    void damage_recieved();

private:
    int direction_;
    int phase_ = 1;
    bool planeHit_ = false;
};
}


#endif // CHARACTER_H
