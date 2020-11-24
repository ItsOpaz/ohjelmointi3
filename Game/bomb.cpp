#include "bomb.h"
#include <QDebug>

namespace Students {

Bomb::Bomb(QPointF pos, int dir)
{
    //bomb gets position and direction from helicopter
    setScale(.07);
    setPixmap(QString(":/graphics/graphics/bomb.svg"));
    setTransformOriginPoint(boundingRect().center());
    setTransformationMode(Qt::SmoothTransformation);
    setPos(pos);
    //dir 1 = North, 2 = South, 3 = East, 4 = West
    switch (dir) {
    case 1:
        setRotation(0);
        break;
    case 2:
        setRotation(180);
        break;
    case 3:
        setRotation(90);
        break;
    case 4:
        setRotation(270);
        break;
    default:
        break;
    }

}

void Bomb::tick()
{
    if(phase_ == 0){
        status_ = false;
    }else if(phase_ == 100){
        explode();
    }else if(phase_ > 100){
        //bomb is scaled smaller every tick so it seems like its dropping
        setScale(.07 * phase_/300);
    }
    phase_ -= 1;
}

void Bomb::explode()
{
    setScale(.1);
    setRotation(0);
    setPixmap(QString(":/graphics/graphics/explosion.svg"));
    emit bombExplosion(this);
}

bool Bomb::status() const
{
    return status_;
}
}
