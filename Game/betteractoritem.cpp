#include "betteractoritem.h"
#include "interfaces/istop.hh"
#include "interfaces/ipassenger.hh"
#include "interfaces/ivehicle.hh"

#include <QDebug>

namespace Students {

BetterActorItem::BetterActorItem(int x, int y, int type)
    :x_(x), y_(y), type_(type)
{
    setPos(mapToParent(x_, y_ ));
    switch (type_) {
    case 1:
        setPixmap(QString(":/graphics/graphics/passenger.svg"));
        setScale(.05);
        break;
    case 2:
        setPixmap(QString(":/graphics/graphics/helicopter.svg"));
        setScale(.05);
        break;
    default:
        int randInt = rand()%5+1;
        qDebug()<<randInt;
        setPixmap(QString(":/graphics/graphics/saab%1.svg").arg(randInt));
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
