#ifndef CHARACTER_H
#define CHARACTER_H

#include "betteractoritem.h"

namespace Students {
class Character : public QGraphicsPixmapItem
{
public:
    Character();
    void move();
    int direction() const;
    void setDirection(int direction);
    void crash();

private:
    int direction_;
};
}


#endif // CHARACTER_H
