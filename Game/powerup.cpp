#include "powerup.h"
#include "plane.h"
#include <QtDebug>

namespace Students {

Powerup::Powerup(int type) : type_(type)
{
    int x = rand() % (X_MAX + X_MIN + 1) - X_MIN;
    int y = rand() % (Y_MAX + Y_MIN + 1) - Y_MIN;
    setPos(x, y);
    setScale(.05);
    setPixmap(QString(":/graphics/graphics/powerup%1.svg").arg(type));
}

int Powerup::getType() const
{
    return type_;
}
}
