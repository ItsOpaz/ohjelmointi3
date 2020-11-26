#include "character.h"
#include <QDebug>
#include <QSound>

namespace Students {


Character::Character()
    :direction_(1)
{
    //helicopter is set top of busstop and bus
    setZValue(3);
    rotorPhase();
    setScale(.15);
    //helicopter originpoint is set to center of boundingrect so rotating helicopter works
    setTransformOriginPoint(this->boundingRect().center());
    setPos(mapToParent(0, 0));
    setTransformationMode(Qt::SmoothTransformation);
}

void Character::move()
{
    rotorPhase();
    //direction 1 = North, 2 = South, 3 = East, 4 = West
    switch (direction_) {
    case 1:
        moveBy(0, -speed_);
        break;
    case 2:
        moveBy(0, speed_);
        break;
    case 3:
        moveBy(speed_, 0);
        break;
    case 4:
        moveBy(-speed_, 0);
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
    emit damage_recieved();
}

void Character::rotorPhase()
{
    //sets helicopter picture for every move so helicopter seems like it's flying
    if(phase_ == 5){
        phase_ = 1;
    }
    setPixmap(QString(":/graphics/graphics/helicopter%1_phase%2.svg").arg(type_).arg(phase_));
    phase_ += 1;
}

Bomb *Character::dropBomb()
{
    return new Bomb(this->pos(), direction());
}

void Character::planeHit(bool status)
{
    if(planeHit_ != status && planeHit_ == false){
        crash();
    }
    planeHit_ = status;
}

void Character::wallhit()
{
    if(this->pos().rx() < -165 || this->pos().rx() > 905 || this->pos().ry() < -165 || this->pos().ry() > 370){
        if(direction_ % 2 == 0){
            direction_ --;
        }else{
            direction_ ++;
        }
        setRotation(rotation()+180);
        crash();
    }
}

void Character::transfrom()
{
    setScale(0.1);
    type_ = 2;
    speed_ = 1.5;
}

int Character::getType() const
{
    return type_;
}


}

