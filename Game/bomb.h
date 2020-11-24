#ifndef BOMB_H
#define BOMB_H

#include <QObject>
#include <QGraphicsPixmapItem>

namespace Students {
class Bomb :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bomb(QPointF, int);
    void tick();
    void explode();
    bool status() const;

signals:
    void bombExplosion(Bomb*);

private:
    int phase_ = 300;
    bool status_ = true;
};
}

#endif // BOMB_H
