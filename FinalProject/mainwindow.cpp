#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
/*
    styleLabel = new QLabel("line style");    //全都是线性的风格
    styleComboBox = new QComboBox;
    styleComboBox->addItem("SolidLine",static_cast<int>(Qt::SolidLine));
    styleComboBox->addItem("DashLine",static_cast<int>(Qt::DashLine));
    styleComboBox->addItem("DotLine",static_cast<int>(Qt::DotLine));
    styleComboBox->addItem("DashDotLine",static_cast<int>(Qt::DashDotLine));
    styleComboBox->addItem("DashDotDotLine",static_cast<int>(Qt::DashDotDotLine));
*/

    setWindowTitle("xwj's paint");
    MyPainter *paintWidget = new MyPainter(this);
    setCentralWidget(paintWidget);


    connect(ui->actionLine, SIGNAL(triggered()), this, SLOT(drawLineActionTriggered()));
    connect(ui->actionEllipse, SIGNAL(triggered()), this, SLOT(drawEllipseActionTriggered()));
    connect(ui->actionCircle, SIGNAL(triggered()), this, SLOT(drawCircleActionTriggered()));
    connect(ui->actionPolygon, SIGNAL(triggered()), this, SLOT(drawPolygonActionTriggered()));
    connect(this, SIGNAL(changeCurrentShape(shapeCode)), paintWidget, SLOT(setCurrentShape(shapeCode)));

    connect(ui->action_width1, SIGNAL(triggered()), this, SLOT(setWidth1()));
    connect(ui->action_width3, SIGNAL(triggered()), this, SLOT(setWidth3()));
    connect(ui->action_width5, SIGNAL(triggered()), this, SLOT(setWidth5()));
    connect(this, SIGNAL(changePainterWidth(int)), paintWidget, SLOT(setCurrentWidth(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawLineActionTriggered()
{
    emit changeCurrentShape(code_line);
}

void MainWindow::drawEllipseActionTriggered()
{
    emit changeCurrentShape(code_ellipse);
}

void MainWindow::drawCircleActionTriggered()
{
    emit changeCurrentShape(code_circle);
}

void MainWindow::drawPolygonActionTriggered()
{
    emit changeCurrentShape(code_polygon);
}


void MainWindow::setWidth1()
{
    emit changePainterWidth(1);
}

void MainWindow::setWidth3()
{
    emit changePainterWidth(3);
}

void MainWindow::setWidth5()
{
    emit changePainterWidth(5);
}
