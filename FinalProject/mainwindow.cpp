#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    styleLabel = new QLabel("line style");    //全都是线性的风格
    styleComboBox = new QComboBox;
    styleComboBox->addItem("SolidLine",static_cast<int>(Qt::SolidLine));
    styleComboBox->addItem("DashLine",static_cast<int>(Qt::DashLine));
    styleComboBox->addItem("DotLine",static_cast<int>(Qt::DotLine));
    styleComboBox->addItem("DashDotLine",static_cast<int>(Qt::DashDotLine));
    styleComboBox->addItem("DashDotDotLine",static_cast<int>(Qt::DashDotDotLine));



    MyPainter *paintWidget = new MyPainter(this);
    setCentralWidget(paintWidget);


    connect(ui->actionLine, SIGNAL(triggered()), this, SLOT(drawLineActionTriggered()));
    connect(ui->actionEllipse, SIGNAL(triggered()), this, SLOT(drawRectActionTriggered()));
    connect(this, SIGNAL(changeCurrentShape(shapeCode)), paintWidget, SLOT(setCurrentShape(shapeCode)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawLineActionTriggered()
{
        emit changeCurrentShape(code_line);
}

void MainWindow::drawRectActionTriggered()
{
        emit changeCurrentShape(code_circle);
}
