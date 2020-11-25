#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include "statistics.h"
#include "bettermainwindow.h"

namespace Ui {
class gameover;
}

namespace Students {
class gameover : public QDialog
{
    Q_OBJECT

public:
    gameover(BetterMainWindow *parent);
    ~gameover();

private slots:
    void on_pushButton_quit_clicked();

private:
    Ui::gameover *ui;
    statistics* stats_;
};
}



#endif // GAMEOVER_H
