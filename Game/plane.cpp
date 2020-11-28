#include "plane.h"
#include <QDebug>

namespace Students {

Plane::Plane()
{
    srand(time(0));
    //plane is set on top of bustops, busses and helicopter
    setZValue(4);
    setScale(.07);
    //direction of plane is randomized and plane pos will depend on it
    direction_ = rand() % 4;
    //plane speed will be random between 1 and 2
    speed_ = rand() % 2 + 1;
    //plane originpoint is set to center of boundingrect so rotating helicopter works
    setTransformOriginPoint(this->boundingRect().center());
    setTransformationMode(Qt::SmoothTransformation);
    setPixmap(QString(":/graphics/graphics/plane.svg"));
    //planes starting position will be randomly on edge of map
    switch (direction_) {
    case 0:{
        int x = rand() % (X_MAX + X_MIN + 1) - X_MIN;
        setPos(x, Y_MAX);
        setRotation(0);
        break;
    }
    case 1:{
        int x = rand() % (X_MAX + X_MIN + 1) - X_MIN;
        setPos(x, Y_MIN);
        setRotation(180);
        break;
    }
    case 2:{
        int y = rand() % (Y_MAX + Y_MIN + 1) - Y_MIN;
        setPos(X_MIN, y);
        setRotation(90);
        break;
    }
    case 3:{
        int y = rand() % (Y_MAX + Y_MIN + 1) - Y_MIN;
        setPos(X_MAX, y);
        setRotation(270);
        break;
    }
    default:
        break;
    }
}

bool Plane::checkPos()
{
    if(this->pos().x() < X_MIN || this->pos().x() > X_MAX || this->pos().y() < Y_MIN || this->pos().y() > Y_MAX){
        emit removePlane(this);
        return false;
    }else{
        return true;
    }
}

void Plane::move()
{
    if(checkPos() && status()){
        switch (direction_) {
        case 0:
            this->moveBy(0, -speed_);
            break;
        case 1:
            this->moveBy(0, speed_);
            break;
        case 2:
            this->moveBy(speed_, 0);
            break;
        case 3:
            this->moveBy(-speed_, 0);
            break;
        default:
            break;
        }

    }
}

void Plane::destroy()
{
    //destroyed plane will be inactive and pixmap is set
    status_ = false;
    setPixmap(QString(":/graphics/graphics/plane_destroyed.svg"));
}

bool Plane::status() const
{
    return status_;
}
}
