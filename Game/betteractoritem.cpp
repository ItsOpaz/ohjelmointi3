#include "betteractoritem.h"
#include "interfaces/istop.hh"
#include "interfaces/ipassenger.hh"
#include "interfaces/ivehicle.hh"

#include <QDebug>

namespace Students {

BetterActorItem::BetterActorItem(int x, int y, int points, bool isStop)
    :x_(x), y_(y), points_(points), isStop_(isStop)
{
    setTransformationMode(Qt::SmoothTransformation);
    setPos(x_, y_);
    setTransformOriginPoint(boundingRect().center());
    if(isStop_){
        setOffset(0, -150);
        setPixmap(QString(":/graphics/graphics/kela.svg"));
        setScale(.07);
        setZValue(0);
    }else{
        setBusColor();
        setScale(.05);
        setZValue(1);
    }
}

BetterActorItem::~BetterActorItem()
{

}

void BetterActorItem::setCoord(int x, int y)
{
    setX( x );
    setY( y );
}

void BetterActorItem::setBusColor()
{
    if(points_ < 5){
        setPixmap(QString(":/graphics/graphics/saab1.svg"));
    }else if(points_ < 10){
        setPixmap(QString(":/graphics/graphics/saab2.svg"));
    }else{
        setPixmap(QString(":/graphics/graphics/saab3.svg"));
    }
}

int BetterActorItem::points() const
{
    return points_;
}

void BetterActorItem::setPoints(int points)
{
    points_ = points;
    setBusColor();
}
}
