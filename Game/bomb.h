#ifndef BOMB_H
#define BOMB_H


#include <QGraphicsPixmapItem>

namespace Students {
class Bomb : public QGraphicsPixmapItem
{
public:
    Bomb(QPointF, int);
    void tick();
    void explode();
    int status() const;

private:
    int phase_ = 300;
    int status_ = 0;
};
}

#endif // BOMB_H
