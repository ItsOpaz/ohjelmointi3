#include "betteractoritem.h"
#include "interfaces/istop.hh"
#include "interfaces/ipassenger.hh"
#include "interfaces/ivehicle.hh"

#include <QDebug>

namespace Students {

BetterActorItem::BetterActorItem(int x, int y, int points, bool isStop)
    :x_(x), y_(y), points_(points), isStop_(isStop)
{
    setTransformOriginPoint(boundingRect().center());
//    setTransformationMode(Qt::SmoothTransformation);
    setPos(mapToParent(x_, y_ ));
    if(isStop_){
        setPixmap(QString(":/graphics/graphics/busstop.svg"));
        setScale(.1);
    }else{
        setBusColor();
        setScale(.03);
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
        setPixmap(QString(":/graphics/graphics/saab6.svg"));
    }else if(points_ < 10){
        setPixmap(QString(":/graphics/graphics/saab2.svg"));
    }else{
        setPixmap(QString(":/graphics/graphics/saab4.svg"));
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
