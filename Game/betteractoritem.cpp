#include "betteractoritem.h"
#include "interfaces/istop.hh"
#include "interfaces/ipassenger.hh"
#include "interfaces/ivehicle.hh"

#include <QDebug>

namespace Students {

BetterActorItem::BetterActorItem(int x, int y, int type)
    :x_(x), y_(y), type_(type)
{
    setTransformOriginPoint(boundingRect().center());
    setPos(mapToParent(x_, y_ ));
    if(type_ == 1){
        setPixmap(QString(":/graphics/graphics/passenger.svg"));
        setScale(.05);
    }else{
        int randInt = rand()%5+1;
        setPixmap(QString(":/graphics/graphics/saab%1.svg").arg(randInt));
        setScale(.07);
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
}
