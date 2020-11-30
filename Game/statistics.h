#ifndef STATISTICS_H
#define STATISTICS_H
#include "QString"
#include <QObject>

/**
 *@file
 * @brief Defines a class for saving statistics of current session
 */

namespace Students {

class statistics
{
public:
    statistics();

    void increase_score(int amount);
    void bomb_dropped();

    //Increase ticks
    void tick_counter();

    //Sets playername and difficulty
    void set_info(QString player_name, QString difficulty);
    void set_lifes(int);

    //Get functions for values
    int get_bombs_amount();
    int get_time();
    int get_buses_destroyed();
    int get_lifes();
    std::pair<QString, int> get_score();
    QString getDifficulty() const;

    void reduce_lifes();

private:
    int score_ = 0;
    int bombs_dropped_ = 0;
    unsigned long int ticks_ = 0;
    int lifes_ = 3;
    QString player_name_;
    QString difficulty_;
};
}




#endif // STATISTICS_H
