#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include "bomb.h"

namespace Students {
class Character : public QGraphicsPixmapItem
{
public:
    Character();
    void move();
    int direction() const;
    void setDirection(int direction);
    void crash();
    void rotorPhase();
    Bomb* dropBomb();

private:
    int direction_;
    int phase_ = 1;
};
}


#endif // CHARACTER_H
