#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mypainter.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyPainter *paintWidget = new MyPainter(this);
    setCentralWidget(paintWidget);


    connect(ui->actionLine, SIGNAL(triggered()), this, SLOT(drawLineActionTriggered()));
    connect(ui->actionEllipse, SIGNAL(triggered()), this, SLOT(drawEllipseActionTriggered()));
    connect(ui->actionCircle, SIGNAL(triggered()), this, SLOT(drawCircleActionTriggered()));
    connect(ui->actionRect, SIGNAL(triggered()), this, SLOT(drawRectActionTriggered()));
    connect(ui->actionPolygon, SIGNAL(triggered()), this, SLOT(drawPolygonActionTriggered()));
    connect(this, SIGNAL(changeCurrentMode(modeCode)), paintWidget, SLOT(setCurrentMode(modeCode)));

    ui->actionLine->setChecked(true);
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
    ui->actionFill->setChecked(false);

    emit changeCurrentMode(code_line);
}

void MainWindow::drawEllipseActionTriggered()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(true);
    ui->actionRect->setChecked(false);
    ui->actionPolygon->setChecked(false);
    ui->actionFill->setChecked(false);

    emit changeCurrentMode(code_ellipse);
}

void MainWindow::drawCircleActionTriggered()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(true);
    ui->actionEllipse->setChecked(false);
    ui->actionRect->setChecked(false);
    ui->actionPolygon->setChecked(false);
    ui->actionFill->setChecked(false);

    emit changeCurrentMode(code_circle);
}

void MainWindow::drawRectActionTriggered()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(false);
    ui->actionRect->setChecked(true);
    ui->actionPolygon->setChecked(false);
    ui->actionFill->setChecked(false);

    emit changeCurrentMode(code_rect);
}

void MainWindow::drawPolygonActionTriggered()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(false);
    ui->actionRect->setChecked(false);
    ui->actionPolygon->setChecked(true);
    ui->actionFill->setChecked(false);

    emit changeCurrentMode(code_polygon);
}

