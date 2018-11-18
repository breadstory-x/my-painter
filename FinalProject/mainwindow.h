#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include<QComboBox>
#include "mypainter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void changeCurrentShape(shapeCode newShape);
    void changePainterWidth(int x);

public slots:
    void drawLineActionTriggered();
    void drawEllipseActionTriggered();
    void drawCircleActionTriggered();
    void drawPolygonActionTriggered();
    void setWidth1();
    void setWidth3();
    void setWidth5();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H


