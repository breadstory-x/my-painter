#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QDebug>
#include<QMessageBox>

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

    setWindowTitle("cg2018:my paint");
    MyPainter *paintWidget = new MyPainter(this);
    setCentralWidget(paintWidget);

    //工具栏
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(OpenButtonClicked()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(SaveButtonClicked()));
    connect(this, SIGNAL(selectFilePath(QString)),paintWidget,SLOT(SaveFile(QString)));

    connect(ui->actionLine, SIGNAL(triggered()), this, SLOT(drawLineActionTriggered()));
    connect(ui->actionEllipse, SIGNAL(triggered()), this, SLOT(drawEllipseActionTriggered()));
    connect(ui->actionCircle, SIGNAL(triggered()), this, SLOT(drawCircleActionTriggered()));
    connect(ui->actionRect, SIGNAL(triggered()), this, SLOT(drawRectActionTriggered()));
    connect(ui->actionPolygon, SIGNAL(triggered()), this, SLOT(drawPolygonActionTriggered()));
    connect(ui->actionFill,SIGNAL(triggered()), this, SLOT(fillActionTriggered()));
    connect(this, SIGNAL(changeCurrentMode(modeCode)), paintWidget, SLOT(setCurrentMode(modeCode)));

    connect(ui->actionColor, SIGNAL(triggered()), this, SLOT(ColorButtonClicked()));
    connect(this, SIGNAL(changeCurrentColor(QColor)),paintWidget,SLOT(setCurrentColor(QColor)));

    //菜单栏
    connect(ui->action_S, SIGNAL(triggered()), this, SLOT(SaveButtonClicked()));
    connect(this, SIGNAL(selectFilePath(QString)),paintWidget,SLOT(SaveFile(QString)));

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
    ui->actionRect->setChecked(false);
    ui->actionPolygon->setChecked(false);
    ui->actionFill->setChecked(false);
    emit changeCurrentMode(code_ellipse);
}

void MainWindow::drawCircleActionTriggered()
{
    ui->actionLine->setChecked(false);
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
    ui->actionFill->setChecked(false);
    emit changeCurrentMode(code_polygon);
}

void MainWindow::fillActionTriggered()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(false);
    ui->actionRect->setChecked(false);
    ui->actionPolygon->setChecked(false);
    emit changeCurrentMode(code_fill);
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

void MainWindow::ColorButtonClicked()
{
    QColor color = QColorDialog::getColor(Qt::black);
    emit changeCurrentColor(color);
}

void MainWindow::SaveButtonClicked()
{
    QString file_path = QFileDialog::getSaveFileName(this, "Select Path", "./NewPicture","Images (*.jpg);;All Files (*)");//第三个参数为打开对话框时的路径
    if(!file_path.isEmpty())
        emit selectFilePath(file_path);
    //qDebug() << file_path;
}

void MainWindow::OpenButtonClicked()
{
    QMessageBox::about(NULL, "About", u8"功能尚未实现");
}
