#ifndef PLANE_H
#define PLANE_H

#include <QObject>
#include <QGraphicsPixmapItem>

const int X_LOWEST = 0;
const int X_HIGHEST = 1095;
const int Y_MIN = 0;
const int Y_MAX = 592;

namespace Students {

class Plane : public QGraphicsPixmapItem
{
public:
    Plane();
    bool checkPos();
    void move();
    void destroy();
    bool status() const;

private:
    int direction_;
    int speed_;
    bool status_;
};
}

#endif // PLANE_H
