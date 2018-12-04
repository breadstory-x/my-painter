#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"mypainter.h"

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
    void changeCurrentMode(modeCode newMode);

public slots:
    void drawLineActionTriggered();
    void drawEllipseActionTriggered();
    void drawCircleActionTriggered();
    void drawRectActionTriggered();
    void drawPolygonActionTriggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
