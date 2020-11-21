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
    BetterActorItem(int x, int y, int type);
    virtual ~BetterActorItem();
    void setCoord(int x, int y);

protected:
    int x_;
    int y_;
    int type_;
};

}

#endif // BETTERACTORITEM_H
