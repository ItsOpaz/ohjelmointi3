#ifndef POWERUP_H
#define POWERUP_H

#include <QGraphicsPixmapItem>

/**
 *@file
 * @brief Defines a class for powerups
 */


namespace Students {

class Powerup : public QGraphicsPixmapItem
{
public:
    Powerup(int);
    int getType() const;

private:
    int type_;
};
}

#endif // POWERUP_H
