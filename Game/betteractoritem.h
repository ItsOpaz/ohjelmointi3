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
    BetterActorItem(int, int, int, bool);
    virtual ~BetterActorItem();
    void setCoord(int, int);
    void setBusColor();
    int points() const;
    void setPoints(int);

protected:
    int points_;
    bool isStop_;
};

}

#endif // BETTERACTORITEM_H
