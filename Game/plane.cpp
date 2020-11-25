#include "plane.h"
#include <QDebug>

namespace Students {

Plane::Plane()
{
    //plane is set on top of bustops, busses and helicopter
    setZValue(4);
    setScale(.07);
    direction_ = rand() % 4;
    speed_ = rand() % 2 + 1;
    //plane originpoint is set to center of boundingrect so rotating helicopter works
    setTransformOriginPoint(this->boundingRect().center());
    setTransformationMode(Qt::SmoothTransformation);
    setPixmap(QString(":/graphics/graphics/plane.svg"));
    switch (direction_) {
    case 0:{
        int x = rand() % (X_HIGHEST + X_HIGHEST + 1) - X_LOWEST;
        setPos(x, Y_MAX);
        setRotation(0);
        break;
    }
    case 1:{
        int x = rand() % (X_HIGHEST + X_HIGHEST + 1) - X_LOWEST;
        setPos(x, Y_MIN);
        setRotation(180);
        break;
    }
    case 2:{
        int y = rand() % (Y_MAX + Y_MAX + 1) - Y_MIN;
        setPos(X_LOWEST, y);
        setRotation(90);
        break;
    }
    case 3:{
        int y = rand() % (Y_MAX + Y_MAX + 1) - Y_MIN;
        setPos(X_HIGHEST, y);
        setRotation(270);
        break;
    }
    default:
        break;
    }
}

bool Plane::checkPos()
{
    if(this->pos().x() < X_LOWEST || this->pos().x() > X_HIGHEST || this->pos().y() < Y_MIN || this->pos().y() > Y_MAX){
        return false;
    }else{
        return true;
    }
}

void Plane::move()
{
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

void Plane::destroy()
{
    status_ = false;
    setPixmap(QString(":/graphics/graphics/plane_destroyed.svg"));
}

bool Plane::status() const
{
    return status_;
}
}
