#include "bomb.h"
#include <QDebug>

namespace Students {

Bomb::Bomb(QPointF pos, qreal rotation)
{
    //bomb gets position and rotation from helicopter
    setScale(.07);
    setPixmap(QString(":/graphics/graphics/bomb.svg"));
    setTransformOriginPoint(boundingRect().center());
    setTransformationMode(Qt::SmoothTransformation);
    setPos(pos);
    setZValue(2);
    setRotation(rotation);
}

void Bomb::tick()
{
    //1 second after explosion bomb will be deleted
    if(phase_ == 0){
        delete this;
    //when bomb reaches 200 ticks(2 seconds) it explodes
    }else if(phase_ == 100){
        explode();
    //bomb is scaled smaller every tick so it seems like its dropping
    }else if(phase_ > 100){
        setScale(.07 * phase_/300);
    }
    phase_ -= 1;
}

void Bomb::explode()
{
    setScale(radius);
    setRotation(0);
    setPixmap(QString(":/graphics/graphics/explosion.svg"));
    emit bombExplosion(this);
}

bool Bomb::status() const
{
    return status_;
}

void Bomb::setRadius(double value)
{
    radius = value;
}
}
