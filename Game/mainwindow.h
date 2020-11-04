#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphics/simplemainwindow.hh"


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

private:
    Ui::MainWindow *ui;
    QGraphicsScene *map;
};
}











#endif // MAINWINDOW_H
