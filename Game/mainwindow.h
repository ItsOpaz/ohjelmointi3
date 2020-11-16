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

public slots:
    void setPicture(QImage &img);
private slots:
    void on_pushButton_menu_clicked();
    void update_clock();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<Interface::ICity> city_;
    std::shared_ptr<CourseSide::Logic> logic_;
    QGraphicsScene *map;
};
}











#endif // MAINWINDOW_H
