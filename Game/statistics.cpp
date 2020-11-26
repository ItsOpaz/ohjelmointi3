#include "statistics.h"
#include "QDebug"

namespace Students {

statistics::statistics()
{

}


void Students::statistics::increase_score(int amount)
{
    score_ += amount;
}

void Students::statistics::bomb_dropped()
{
    bombs_dropped_++;
}

void Students::statistics::tick_counter()
{
    ticks_++;
}

void Students::statistics::read_highscore()
{

}

void Students::statistics::set_info(QString player_name, QString difficulty)
{
    player_name_ = player_name;
    difficulty_ = difficulty;
}

void statistics::reduce_lifes()
{
    lifes_--;
}

QString statistics::getDifficulty() const
{
    return difficulty_;
}

int statistics::get_bombs_amount()
{
    return bombs_dropped_;
}

int statistics::get_time()
{
    return ticks_;
}

int statistics::get_lifes()
{
    return lifes_;
}

std::pair<QString, int> statistics::get_score()
{
    std::pair<QString, int> score = {player_name_, score_};
    return score;
}
}


