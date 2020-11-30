#ifndef PLANE_H
#define PLANE_H

#include <QObject>
#include <QGraphicsPixmapItem>

/**
 *@file
 * @brief Defines a class for enemyplanes flying horizontally and vertically in scene
 */


const int X_MIN = 0;
const int X_MAX = 1095;
const int Y_MIN = 0;
const int Y_MAX = 592;

namespace Students {

class Plane : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Plane();

    /**
     * @brief if plane flies out of map it will be removed and removePlane will be emitted
     * @return true if position is valid, false if position is out of map
     */
    bool checkPos();
    /**
     * @brief sets plane status to destroyed and sets correct pixmap
     */
    void destroy();
    bool status() const;

signals:
    /**
     * @brief remove plane signal will emit to bettermainwindow planeremoved slot
     * @param pointer to plane that will be removed
     */
    void removePlane(Plane *);

public slots:
    /**
     * @brief plane is moved every timer tick to correct direction
     */
    void move();

private:
    int direction_;
    int speed_;
    bool status_;
};
}

#endif // PLANE_H
