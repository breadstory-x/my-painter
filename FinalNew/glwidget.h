#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>
#include <QKeyEvent>
#include <vector>
#include<QMouseEvent>
#include<QWheelEvent>

//顶点结构体
struct Vertice
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    Vertice(GLfloat a,GLfloat b,GLfloat c)
    {
        x=a;
        y=b;
        z=c;
    }
};

//面结构体
struct Face
{
    //该面有几个顶点，一般为3或4
    int num;
    //每个顶点在顶点数组的下标
    std::vector<int>vertice_index;
    Face() {}
};

class GLwidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLwidget(QWidget *parent = nullptr);
    void open_file();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *event);//处理键盘按下事件
    void mousePressEvent(QMouseEvent *event);//鼠标点击事件
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动事件
    void wheelEvent(QWheelEvent *event);//鼠标滑轮事件
private:
    bool fullscreen;//是否全屏显示
    GLfloat x_angle;//控制x旋转
    GLfloat y_angle;//控制y旋转
    GLfloat z_angle;//控制z旋转
    GLfloat away; //控制远近
    bool view_type;//显示面还是线条

    QPoint lastPos;

    int vertice_num;//顶点个数
    int face_num;//面个数
    std::vector<Vertice>vertices;//顶点数组
    std::vector<Face>faces;//面数组

signals:

public slots:
};

#endif // GLWIDGET_H
