#ifndef BETTERACTORITEM_H
#define BETTERACTORITEM_H

#include <QGraphicsPixmapItem>

/**
 *@file
 * @brief Defines a class for graphicsitems for stops and actors
 */

namespace Students {

class BetterActorItem : public QGraphicsPixmapItem
{
public:
    BetterActorItem(int, int, int, bool);
    virtual ~BetterActorItem();
    void setCoord(int, int);
    /**
     * @brief buss color will be determined by passengers inside
     */
    void setBusColor();
    int points() const;
    /**
     * @brief sets points for bus by passengers inside
     */
    void setPoints(int);
    /**
     * @brief item is destroyed by bomb
     */
    void destroy();
    int status() const;

protected:
    int points_;
    //isStop will determine if item is stop or bus
    bool isStop_;
    int status_ = true;
};

}

#endif // BETTERACTORITEM_H
