#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphics/simplemainwindow.hh"
#include "city.h"
#include "core/logic.hh"


namespace Ui {
class MainWindow;
}

namespace Students {
class MainWindow : public CourseSide::SimpleMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void drawStops(std::vector<std::shared_ptr<Interface::IStop> >);
    void drawBusses();

public slots:
    void setPicture(QImage img);
private slots:
    void on_pushButton_menu_clicked();
    void update_clock();

private:
    std::shared_ptr<Ui::MainWindow> ui;
    QGraphicsScene *map;
};
}











#endif // MAINWINDOW_H
