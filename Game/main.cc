#include <QApplication>
#include "core/logic.hh"
#include "city.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    CourseSide::Logic game;
    game.fileConfig();
    std::shared_ptr<Students::City> Tampere(new Students::City());
    game.takeCity(Tampere);
    game.finalizeGameStart();
    return a.exec();
}
