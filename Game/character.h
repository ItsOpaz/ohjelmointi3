#ifndef CHARACTER_H
#define CHARACTER_H

#include "betteractoritem.h"

namespace Students {
class Character : public BetterActorItem
{
public:
    Character(int x, int y, int type) : BetterActorItem(x, y, type){};
};
}


#endif // CHARACTER_H
