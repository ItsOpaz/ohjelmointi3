#ifndef BOMB_H
#define BOMB_H

#include <QObject>
#include <QGraphicsPixmapItem>

namespace Students {
class Bomb :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bomb(QPointF, qreal);
    //sets pixmap and emits bombExplosion
    void explode();
    bool status() const;
    //radius for bomb is determined by difficulty
    void setRadius(double value);

public slots:
    //bomb phase will be adjusted every tick
    void tick();

signals:
    //explosion signal will be emited to slot bettermainwindow::explosion
    void bombExplosion(Bomb*);

private:
    //phase determines explosion time at 0 bomb will be deleted
    int phase_ = 300;
    bool status_ = true;
    double radius;
};
}

#endif // BOMB_H
