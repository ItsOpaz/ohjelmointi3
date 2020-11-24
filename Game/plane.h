#ifndef PLANE_H
#define PLANE_H

#include <QObject>
#include <QGraphicsPixmapItem>

namespace Students {

class Plane : public QGraphicsPixmapItem
{
public:
    Plane();
    bool checkPos();
    void move();
private:
    int direction_;
    int speed_;
    int limit_;
};
}

#endif // PLANE_H
