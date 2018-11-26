#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QDebug>
#include<QMessageBox>
#include<QGroupBox>
#include<QLayout>
#include<QSplitter>
#include<QPushButton>
#include<QSpinBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    //创建三组groupbox
    QGroupBox *mainGroup = new QGroupBox(this);
    //mainGroup->setFixedWidth(180);
    mainGroup->setTitle(u8"变换");

    QGroupBox *rotateGroup = new QGroupBox(mainGroup);
    rotateGroup->setTitle(u8"旋转");
    QSlider *rotateSlider = new QSlider(Qt::Horizontal, rotateGroup);
    rotateSlider->setRange(0, 360);
    rotateSlider->setSingleStep(1);//步长
    QSpinBox *rotateSpinBox = new QSpinBox(rotateGroup);
    rotateSpinBox->setMinimum(0);
    rotateSpinBox->setMaximum(360);
    rotateSpinBox->setSingleStep(1);
    //rotateSlider->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    //rotateSlider->setEnabled(false);

    QGroupBox *scaleGroup = new QGroupBox(mainGroup);
    scaleGroup->setTitle(u8"缩放");
    QSlider *scaleSlider = new QSlider(Qt::Horizontal, scaleGroup);
    scaleSlider->setRange(1, 4000);
    scaleSlider->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    //scaleSlider->setEnabled(false);

    //右侧窗口布局
    QVBoxLayout *addWidgetLayout = new QVBoxLayout();//垂直布局
    addWidgetLayout->addWidget(mainGroup);
    addWidgetLayout->addStretch(1);//分隔

    QVBoxLayout *rotateGroupLayout = new QVBoxLayout(rotateGroup);
    rotateGroupLayout->addWidget(rotateSlider);
    rotateGroupLayout->addWidget(rotateSpinBox);

    QVBoxLayout *scaleGroupLayout = new QVBoxLayout(scaleGroup);
    scaleGroupLayout->addWidget(scaleSlider);

    QVBoxLayout *mainGroupLayout = new QVBoxLayout(mainGroup);
    mainGroupLayout->addWidget(rotateGroup);
    mainGroupLayout->addWidget(scaleGroup);



    setWindowTitle("cg2018:my paint");
    MyPainter *paintWidget = new MyPainter(this);
    QWidget *addWidget = new QWidget(this);
    addWidget->setFixedWidth(180);
    addWidget->setLayout(addWidgetLayout);

/*  QSplitter *spliter=new QSplitter;
    spliter->addWidget(paintWidget);
    spliter->addWidget(addWidget);
    spliter->setStretchFactor(0,8);
    spliter->setStretchFactor(1,2);
    setCentralWidget(spliter);*/

    QHBoxLayout *cwLayout = new QHBoxLayout();//水平布局，此处是用一个大窗口装画布和右侧变换工具栏
    cwLayout->addWidget(paintWidget);
    cwLayout->addWidget(addWidget);

    QWidget *cw = new QWidget();
    cw->setLayout(cwLayout);
    setCentralWidget(cw);

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
    connect(ui->actionTransform, SIGNAL(triggered()), this, SLOT(transfromActionTriggered()));
    connect(this, SIGNAL(changeCurrentMode(modeCode)), paintWidget, SLOT(setCurrentMode(modeCode)));

    connect(ui->actionColor, SIGNAL(triggered()), this, SLOT(ColorButtonClicked()));
    connect(this, SIGNAL(changeCurrentColor(QColor)),paintWidget,SLOT(setCurrentColor(QColor)));

    connect(ui->actionSelect, SIGNAL(triggered()), this, SLOT(SelectButtonClicked()));
    connect(this, SIGNAL(changeCurrentMode(modeCode)), paintWidget, SLOT(setCurrentMode(modeCode)));

    connect(ui->actionCut, SIGNAL(triggered()), this, SLOT(cutButtonClicked()));
    connect(this, SIGNAL(cutPicture()), paintWidget, SLOT(doCutPicture()));

    //菜单栏
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(NewButtonClicked()));
    connect(this, SIGNAL(newPixmap()), paintWidget, SLOT(NewFile()));
    connect(ui->action_S, SIGNAL(triggered()), this, SLOT(SaveButtonClicked()));
    connect(this, SIGNAL(selectFilePath(QString)),paintWidget,SLOT(SaveFile(QString)));

    connect(ui->action_width1, SIGNAL(triggered()), this, SLOT(setWidth1()));
    connect(ui->action_width3, SIGNAL(triggered()), this, SLOT(setWidth3()));
    connect(ui->action_width5, SIGNAL(triggered()), this, SLOT(setWidth5()));
    connect(this, SIGNAL(changePainterWidth(int)), paintWidget, SLOT(setCurrentWidth(int)));

    //右窗口
    connect(rotateSlider, SIGNAL(valueChanged(int)), this, SLOT(changeRotation(int)));
    connect(this, SIGNAL(setRotation(int)), paintWidget, SLOT(rotate(int)));
    connect(scaleSlider, SIGNAL(valueChanged(int)), this, SLOT(changeScale(int)));
    connect(this, SIGNAL(setScale(qreal)), paintWidget, SLOT(scale(qreal)));
    //滑动条与微调框
    connect(rotateSpinBox, SIGNAL(valueChanged(int)), rotateSlider, SLOT(setValue(int)));
    connect(rotateSlider, SIGNAL(valueChanged(int)), rotateSpinBox, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeRotation(int r)
{
    emit setRotation(r);
}

void MainWindow::changeScale(int s)
{
    emit setScale(qreal(s) / 1000);
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

void MainWindow::drawLineActionTriggered()
{
    ui->actionLine->setChecked(true);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(false);
    ui->actionPolygon->setChecked(false);
    ui->actionRect->setChecked(false);
    ui->actionFill->setChecked(false);
    ui->actionSelect->setChecked(false);
    ui->actionTransform->setChecked(false);

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
    ui->actionFill->setChecked(false);
    ui->actionSelect->setChecked(false);
    ui->actionTransform->setChecked(false);

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
    ui->actionFill->setChecked(false);
    ui->actionSelect->setChecked(false);
    ui->actionTransform->setChecked(false);

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
    ui->actionFill->setChecked(false);
    ui->actionSelect->setChecked(false);
    ui->actionTransform->setChecked(false);

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
    ui->actionFill->setChecked(false);
    ui->actionSelect->setChecked(false);
    ui->actionTransform->setChecked(false);

    ui->actionCut->setEnabled(false);

    emit changeCurrentMode(code_polygon);
}

void MainWindow::fillActionTriggered()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(false);
    ui->actionRect->setChecked(false);
    ui->actionPolygon->setChecked(false);
    ui->actionFill->setChecked(true);
    ui->actionSelect->setChecked(false);
    ui->actionTransform->setChecked(false);

    ui->actionCut->setEnabled(false);

    emit changeCurrentMode(code_fill);
}

void MainWindow::SelectButtonClicked()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(false);
    ui->actionRect->setChecked(false);
    ui->actionPolygon->setChecked(false);
    ui->actionFill->setChecked(false);
    ui->actionSelect->setChecked(true);
    ui->actionTransform->setChecked(false);

    ui->actionCut->setEnabled(true);

    emit changeCurrentMode(code_select);
}

void MainWindow::transfromActionTriggered()
{
    ui->actionLine->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionEllipse->setChecked(false);
    ui->actionRect->setChecked(false);
    ui->actionPolygon->setChecked(false);
    ui->actionFill->setChecked(false);
    ui->actionSelect->setChecked(false);
    ui->actionTransform->setChecked(true);

    ui->actionCut->setEnabled(false);

    emit changeCurrentMode(code_transform);
}

void MainWindow::cutButtonClicked()
{
    emit cutPicture();
}

void MainWindow::ColorButtonClicked()
{
    QColor color = QColorDialog::getColor(Qt::black);
    emit changeCurrentColor(color);
}

void MainWindow::NewButtonClicked()
{
    emit newPixmap();
}

void MainWindow::OpenButtonClicked()
{
    QMessageBox::about(NULL, "About", u8"功能尚未实现");
}

void MainWindow::SaveButtonClicked()
{
    QString file_path = QFileDialog::getSaveFileName(this, "Select Path", "./NewPicture","Images (*.jpg);;All Files (*)");//第三个参数为打开对话框时的路径
    if(!file_path.isEmpty())
        emit selectFilePath(file_path);
    //qDebug() << file_path;
}


