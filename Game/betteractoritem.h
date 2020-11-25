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
    void destroy();
    int status() const;

protected:
    int points_;
    bool isStop_;
    int status_ = true;
};

}

#endif // BETTERACTORITEM_H
