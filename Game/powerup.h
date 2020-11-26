#ifndef POWERUP_H
#define POWERUP_H

#include <QGraphicsPixmapItem>

class Powerup : public QGraphicsPixmapItem
{
public:
    Powerup(int);
    int getType() const;

private:
    int type_;
};

#endif // POWERUP_H
