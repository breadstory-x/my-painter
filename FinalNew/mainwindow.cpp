#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mypainter.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyPainter *paintWidget = new MyPainter(this);
    setCentralWidget(paintWidget);


    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(SaveButtonClicked()));
    connect(this, SIGNAL(selectFilePath(QString)),paintWidget,SLOT(SaveFile(QString)));

    connect(ui->actionLine, SIGNAL(triggered()), this, SLOT(drawLineActionTriggered()));
    connect(ui->actionEllipse, SIGNAL(triggered()), this, SLOT(drawEllipseActionTriggered()));
    connect(ui->actionCircle, SIGNAL(triggered()), this, SLOT(drawCircleActionTriggered()));
    connect(ui->actionRect, SIGNAL(triggered()), this, SLOT(drawRectActionTriggered()));
    connect(ui->actionPolygon, SIGNAL(triggered()), this, SLOT(drawPolygonActionTriggered()));
    connect(ui->actionCurve, SIGNAL(triggered()), this, SLOT(drawCurveActionTriggered()));
    connect(ui->actionFill,SIGNAL(triggered()), this, SLOT(fillActionTriggered()));
    connect(this, SIGNAL(changeCurrentMode(modeCode)), paintWidget, SLOT(setCurrentMode(modeCode)));

    connect(ui->actionColor, SIGNAL(triggered()), this, SLOT(ColorButtonClicked()));
    connect(this, SIGNAL(changeCurrentColor(QColor)),paintWidget,SLOT(setCurrentColor(QColor)));

    connect(ui->actionSelect, SIGNAL(triggered()), this, SLOT(SelectButtonClicked()));
    connect(this, SIGNAL(changeCurrentMode(modeCode)), paintWidget, SLOT(setCurrentMode(modeCode)));

    connect(ui->actionCut, SIGNAL(triggered()), this, SLOT(cutButtonClicked()));
    connect(this, SIGNAL(cutPicture()), paintWidget, SLOT(doCutPicture()));

    connect(ui->actionLarge, SIGNAL(triggered()), this, SLOT(largeActionTriggered()));
    connect(ui->actionLittle, SIGNAL(triggered()), this, SLOT(littleActionTriggered()));
    connect(this, SIGNAL(emitscale(double)), paintWidget, SLOT(scale(double)));
    ui->actionLine->setChecked(true);
    ui->actionColor->setEnabled(false);
    ui->actionCut->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::drawLineActionTriggered()
{
    ui->actionLine->setChecked(true);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(false);
    ui->actionPolygon->setChecked(false);
    ui->actionRect->setChecked(false);
    ui->actionCurve->setChecked(false);
    ui->actionFill->setChecked(false);
    ui->actionSelect->setChecked(false);

    ui->actionColor->setEnabled(false);
    ui->actionCut->setEnabled(false);

    emit changeCurrentMode(code_line);
}

void MainWindow::drawEllipseActionTriggered()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(true);
    ui->actionRect->setChecked(false);
    ui->actionPolygon->setChecked(false);
    ui->actionCurve->setChecked(false);
    ui->actionFill->setChecked(false);
    ui->actionSelect->setChecked(false);

    ui->actionColor->setEnabled(false);
    ui->actionCut->setEnabled(false);

    emit changeCurrentMode(code_ellipse);
}

void MainWindow::drawCircleActionTriggered()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(true);
    ui->actionEllipse->setChecked(false);
    ui->actionRect->setChecked(false);
    ui->actionPolygon->setChecked(false);
    ui->actionCurve->setChecked(false);
    ui->actionFill->setChecked(false);
    ui->actionSelect->setChecked(false);

    ui->actionColor->setEnabled(false);
    ui->actionCut->setEnabled(false);

    emit changeCurrentMode(code_circle);
}

void MainWindow::drawRectActionTriggered()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(false);
    ui->actionRect->setChecked(true);
    ui->actionPolygon->setChecked(false);
    ui->actionCurve->setChecked(false);
    ui->actionFill->setChecked(false);
    ui->actionSelect->setChecked(false);

    ui->actionColor->setEnabled(false);
    ui->actionCut->setEnabled(false);

    emit changeCurrentMode(code_rect);
}

void MainWindow::drawPolygonActionTriggered()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(false);
    ui->actionRect->setChecked(false);
    ui->actionPolygon->setChecked(true);
    ui->actionCurve->setChecked(false);
    ui->actionFill->setChecked(false);
    ui->actionSelect->setChecked(false);

    ui->actionColor->setEnabled(false);
    ui->actionCut->setEnabled(false);

    emit changeCurrentMode(code_polygon);
}

void MainWindow::drawCurveActionTriggered()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(false);
    ui->actionRect->setChecked(false);
    ui->actionPolygon->setChecked(false);
    ui->actionCurve->setChecked(true);
    ui->actionFill->setChecked(false);
    ui->actionSelect->setChecked(false);

    ui->actionColor->setEnabled(false);
    ui->actionCut->setEnabled(false);

    emit changeCurrentMode(code_curve);
}

void MainWindow::fillActionTriggered()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(false);
    ui->actionRect->setChecked(false);
    ui->actionPolygon->setChecked(false);
    ui->actionCurve->setChecked(false);
    ui->actionFill->setChecked(true);
    ui->actionSelect->setChecked(false);

    ui->actionColor->setEnabled(true);
    ui->actionCut->setEnabled(false);

    emit changeCurrentMode(code_fill);
}

void MainWindow::ColorButtonClicked()
{
    QColor color = QColorDialog::getColor(Qt::black);
    emit changeCurrentColor(color);
}

void MainWindow::largeActionTriggered()
{
    emit emitscale(1.25);
}

void MainWindow::littleActionTriggered()
{
    emit emitscale(0.8);
}

void MainWindow::SelectButtonClicked()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(false);
    ui->actionRect->setChecked(false);
    ui->actionPolygon->setChecked(false);
    ui->actionFill->setChecked(false);
    ui->actionCurve->setChecked(false);
    ui->actionSelect->setChecked(true);

    ui->actionColor->setEnabled(false);
    ui->actionCut->setEnabled(true);

    emit changeCurrentMode(code_select);
}

void MainWindow::cutButtonClicked()
{
    emit cutPicture();
}

void MainWindow::SaveButtonClicked()
{
    QString file_path = QFileDialog::getSaveFileName(this, "Select Path", "./NewPicture","Images (*.jpg);;All Files (*)");//第三个参数为打开对话框时的路径
    if(!file_path.isEmpty())
        emit selectFilePath(file_path);
    //qDebug() << file_path;
}
