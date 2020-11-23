#include "character.h"
#include <QDebug>

namespace Students {


Character::Character()
    :direction_(1)
{
    setPixmap(QString(":/graphics/graphics/helicopter.svg"));
    setScale(.05);
    setTransformOriginPoint(this->boundingRect().center());
    setPos( 200,-100);
}

void Character::move()
{
    switch (direction_) {
    case 1:
        moveBy(0, -1);
        this->setRotation(0);
        break;
    case 2:
        moveBy(0, 1);
        this->setRotation(180);
        break;
    case 3:
        moveBy(1, 0);
        this->setRotation(90);
        break;
    case 4:
        moveBy(-1, 0);
        this->setRotation(270);
        break;
    default:
        break;
    }
}

int Character::direction() const
{
    return direction_;
}

void Character::setDirection(int direction)
{
    direction_ = direction;
}

void Character::crash()
{
    if (this->pos().rx() < -347 || this->pos().rx() > 738 || this->pos().ry() < -403 || this->pos().ry() > 184){
        qDebug()<<"meni heti vituiks";
    }
}


}

