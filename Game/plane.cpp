#include "plane.h"
#include <QDebug>

namespace Students {

Plane::Plane()
{
    //plane is set on top of bustops, busses and helicopter
    setZValue(2);
    setScale(.1);
    direction_ = rand() % 4;
    speed_ = rand() % 5 ;
    //plane originpoint is set to center of boundingrect so rotating helicopter works
    setTransformOriginPoint(this->boundingRect().center());
    setTransformationMode(Qt::SmoothTransformation);
    setPixmap(QString(":/graphics/graphics/helicopter_phase4.svg"));
    switch (direction_) {
    case 0:{
        limit_ = -173;
        int x = rand() % 1097 - 173;
        setPos(mapToParent(x, 378));
        setRotation(0);
        break;
    }
    case 1:{
        limit_ = 378;
        int x = rand() % 1097 - 173;
        setPos(mapToParent(x, -173));
        setRotation(180);
        break;
    }
    case 2:{
        limit_ = 924;
        int y = rand() % 551 - 173;
        setPos(mapToParent(-173, y));
        setRotation(90);
        break;
    }
    default:
        limit_ = -173;
        int y = rand() % 551 - 173;
        setPos(mapToParent(924, y));
        setRotation(270);
        break;
    }
}

bool Plane::checkPos()
{
    switch (direction_) {
    case 0:
        if(pos().y() < limit_){return false;}
        return true;
    case 1:
        if(pos().y() > limit_){return false;}
        return true;
    case 2:
        if(pos().x() > limit_){return false;}
        return true;
    default:
        if(pos().x() < limit_){return false;}
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
    default:
        this->moveBy(-speed_, 0);
        break;
    }
}
}
