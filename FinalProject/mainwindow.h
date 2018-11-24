#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include<QComboBox>
#include<QColor>
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
    void changeCurrentMode(modeCode newMode);
    void changePainterWidth(int x);
    void changeCurrentColor(QColor c);
    void selectFilePath(QString s);

public slots:
    void drawLineActionTriggered();
    void drawEllipseActionTriggered();
    void drawCircleActionTriggered();
    void drawRectActionTriggered();
    void drawPolygonActionTriggered();
    void fillActionTriggered();
    void setWidth1();
    void setWidth3();
    void setWidth5();
    void ColorButtonClicked();
    void SaveButtonClicked();
    void OpenButtonClicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H


