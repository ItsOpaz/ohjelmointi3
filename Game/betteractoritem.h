#ifndef BETTERACTORITEM_H
#define BETTERACTORITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>
#include "interfaces/iactor.hh"

namespace Students {

class BetterActorItem : public QGraphicsPixmapItem
{
public:
    BetterActorItem(int, int, int);
    virtual ~BetterActorItem();
    void setCoord(int, int);

protected:
    int x_;
    int y_;
    int type_;
};

}

#endif // BETTERACTORITEM_H
