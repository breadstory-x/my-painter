#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QColorDialog>
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
    void emitscale(double x);
    void changeCurrentColor(QColor);
    void cutPicture();
    void selectFilePath(QString s);
    void cleanPixmap();

public slots:
    void drawLineActionTriggered();
    void drawEllipseActionTriggered();
    void drawCircleActionTriggered();
    void drawRectActionTriggered();
    void drawPolygonActionTriggered();
    void drawCurveActionTriggered();
    void fillActionTriggered();

    void ColorButtonClicked();

    void largeActionTriggered();
    void littleActionTriggered();

    void SelectButtonClicked();
    void cutButtonClicked();
    void SaveButtonClicked();
    void OpenButtonClicked();
    void CleanButtonClicked();

    void helpActionTriggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
