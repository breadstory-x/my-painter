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

public slots:
    void drawLineActionTriggered();
    void drawRectActionTriggered();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
