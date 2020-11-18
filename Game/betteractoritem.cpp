#include "betteractoritem.h"
#include "interfaces/istop.hh"
#include "interfaces/ipassenger.hh"
#include "interfaces/ivehicle.hh"

namespace Students {

BetterActorItem::BetterActorItem(int x, int y, int type)
    :x_(x), y_(y), type_(type)
{
    setPos(mapToParent(x_, y_ ));
    if(type == 1){
        setPixmap(QString(":/graphics/graphics/passenger.svg"));
        setScale(.05);
    }else{
        setPixmap(QString(":/graphics/graphics/saab1.svg"));
        setScale(.1);
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
