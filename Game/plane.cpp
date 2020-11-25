#include "plane.h"
#include <QDebug>

namespace Students {

Plane::Plane()
{
    //plane is set on top of bustops, busses and helicopter
    setZValue(4);
    setScale(.1);
    direction_ = rand() % 4;
    speed_ = rand() % 5 + 1;
    //plane originpoint is set to center of boundingrect so rotating helicopter works
    setTransformOriginPoint(this->boundingRect().center());
    setTransformationMode(Qt::SmoothTransformation);
    setPixmap(QString(":/graphics/graphics/plane.svg"));
    switch (direction_) {
    case 0:{
        limit_ = 0;
        int x = rand() % 1097;
        setPos(mapToScene(x, 550));
        setRotation(0);
        break;
    }
    case 1:{
        limit_ = 550;
        int x = rand() % 1097;
        setPos(mapToScene(x, 0));
        setRotation(180);
        break;
    }
    case 2:{
        limit_ = 1097;
        int y = rand() % 550;
        setPos(mapToScene(0, y));
        setRotation(90);
        break;
    }
    case 3:{
        limit_ = 0;
        int y = rand() % 550;
        setPos(mapToScene(1097, y));
        setRotation(270);
        break;
    }
    default:
        break;
    }
}

bool Plane::checkPos()
{
    switch (direction_) {
    case 0:
        if(this->scenePos().y() < limit_){return false;}
        return true;
    case 1:
        if(this->scenePos().y() > limit_){return false;}
        return true;
    case 2:
        if(this->scenePos().x() > limit_){return false;}
        return true;
    case 3:
        if(this->scenePos().x() < limit_){return false;}
        return true;
    default:
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
