#ifndef PLANE_H
#define PLANE_H

#include <QObject>
#include <QGraphicsPixmapItem>

const int X_MIN = 0;
const int X_MAX = 1095;
const int Y_MIN = 0;
const int Y_MAX = 592;

namespace Students {

class Plane : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Plane();
    //if plane flies out of map it will be removed and removePlane will be emitted
    bool checkPos();
    void destroy();
    bool status() const;

signals:
    //remove plane signal will emit to bettermainwindow planeremoved slot
    void removePlane(Plane *);

public slots:
    //plane is moved every timer tick to correct direction
    void move();

private:
    int direction_;
    int speed_;
    bool status_;
};
}

#endif // PLANE_H
