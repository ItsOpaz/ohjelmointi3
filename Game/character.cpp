#include "character.h"
#include <QDebug>

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
        moveBy(0, -1);
        this->setRotation(0);
        emit moveVerticalScroll(pos().y()*4+250);
        break;
    case 2:
        moveBy(0, 1);
        this->setRotation(180);
        emit moveVerticalScroll(pos().y()*4+250);
        break;
    case 3:
        moveBy(1, 0);
        this->setRotation(90);
        emit moveHorizontalScroll(pos().x()*4-250);
        break;
    case 4:
        moveBy(-1, 0);
        this->setRotation(270);
        emit moveHorizontalScroll(pos().x()*4-250);
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

void Character::crash(bool crash)
{
    if (this->pos().x() < -173 || this->pos().x() > 924 || this->pos().y() < -173 || this->pos().y() > 378){
        qDebug()<<"ajoit harhaan";
    }
    if(crash){
        qDebug()<<"mikä vittu siinä on ku pitää itteensä ampua";
    }
}

void Character::rotorPhase()
{
    //sets helicopter picture for every move so helicopter seems like it's flying
    switch (phase_) {
    case 1:
        setPixmap(QString(":/graphics/graphics/helicopter_phase1.svg"));
        break;
    case 2:
        setPixmap(QString(":/graphics/graphics/helicopter_phase2.svg"));
        break;
    case 3:
        setPixmap(QString(":/graphics/graphics/helicopter_phase3.svg"));
        break;
    default:
        setPixmap(QString(":/graphics/graphics/helicopter_phase4.svg"));
        phase_ = 0;
        break;
    }
    phase_ += 1;
}

Bomb *Character::dropBomb()
{
    return new Bomb(this->pos(), direction());
}


}

