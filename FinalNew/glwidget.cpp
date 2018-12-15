#include "glwidget.h"

GLwidget::GLwidget(QWidget *parent) : QGLWidget(parent)
{
    fullscreen = false;
    x_angle = 0.0f;
    y_angle = 0.0f;
    z_angle = 0.0f;
    away = -6.0f;
    view_type = true;
    open_file();
}

void GLwidget::open_file()
{
    QString filename = QFileDialog::getOpenFileName();
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }

    //读第一行,判断是否为OFF文件
    QByteArray line1 = file.readLine();
    QString str1(line1);
    QStringList list1 = str1.split("\n");
    if(list1[0] != "OFF")
    {
        QMessageBox::information(NULL,"error",u8"不是OFF格式的文件\n");
        qDebug()<<str1<<list1;
        return;
    }
    //读第二行，获取顶点数和面数
    QByteArray line2 = file.readLine();
    QString str2(line2);
    vertice_num = str2.section(" ",0,0).toInt();
    face_num = str2.section(" ",1,1).toInt();

    //读取点的坐标
    for(int i = 0;i<vertice_num;i++)
    {
        QByteArray line_v = file.readLine();
        QString str_v(line_v);
        QString x = str_v.section(" ",0,0);
        QString y = str_v.section(" ",1,1);
        QString z = str_v.section(" ",2,2);
        Vertice temp(x.toFloat(),y.toFloat(),z.toFloat());
        vertices.push_back(temp);
    }

    //读取面
    for(int i = 0;i<face_num;i++)
    {
        QByteArray line_f = file.readLine();
        QString str_f(line_f);
        Face temp2;
        temp2.num = str_f.section(" ",0,0).toInt();//获取该面的顶点个数
        for(int j = 0;j<temp2.num;j++)
        {
            temp2.vertice_index.push_back(str_f.section(" ",j+1,j+1).toInt());
        }
        faces.push_back(temp2);
    }
}


void GLwidget::initializeGL()
{
    //m_Texture = bindTexture(QPixmap(m_FileName));       //载入位图并转换成纹理
    //glEnable(GL_TEXTURE_2D);                            //启用纹理映射

    glClearColor(0.0, 0.0, 0.0, 0.0);                   //黑色背景
    glShadeModel(GL_SMOOTH);                            //启用阴影平滑

    glClearDepth(1.0);                                  //设置深度缓存
    glEnable(GL_DEPTH_TEST);                            //启用深度测试
    glDepthFunc(GL_LEQUAL);                             //所作深度测试的类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //告诉系统对透视进行修正

    /*GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};  //环境光参数
    GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  //漫散光参数
    GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f}; //光源位置
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);     //设置环境光
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);     //设置漫射光
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   //设置光源位置
    glEnable(GL_LIGHT1);                                //启动一号光源
    */
}

void GLwidget::resizeGL(int w, int h)
{

    glViewport(0, 0, (GLint)w, (GLint)h);               //重置当前的视口
    glMatrixMode(GL_PROJECTION);                        //选择投影矩阵
    glLoadIdentity();                                   //重置投影矩阵
    //设置视口的大小
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);                         //选择模型观察矩阵
    glLoadIdentity();                                   //重置模型观察矩阵
}

void GLwidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);  //清除屏幕和深度缓存
    glLoadIdentity();                                   //重置当前的模型观察矩阵
    glTranslatef(0.0f, 0.0f, away);
    glRotatef(x_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(y_angle, 0.0f, 1.0f, 0.0f);
    glRotatef(z_angle, 0.0f, 0.0f, 1.0f);

    int type;
    if(faces.size()>0 && faces[0].num == 3)
        type = GL_TRIANGLES;
    else if(faces.size()>0 && faces[0].num == 4)
        type = GL_QUADS;

    if(view_type)
    {
        glBegin(type);
            for(int i = 0;i<face_num;i++)
            {
                //glColor3f(1.0f, 1.0f, 0.8f);
                glColor3f(0.5f, 0.5f, 1.0f);
                glVertex3f(vertices[faces[i].vertice_index[0]].x,vertices[faces[i].vertice_index[0]].y,vertices[faces[i].vertice_index[0]].z);
                glColor3f(0.6f, 0.4f, 1.0f);
                glVertex3f(vertices[faces[i].vertice_index[1]].x,vertices[faces[i].vertice_index[1]].y,vertices[faces[i].vertice_index[1]].z);
                glColor3f(0.4f, 0.6f, 1.0f);
                glVertex3f(vertices[faces[i].vertice_index[2]].x,vertices[faces[i].vertice_index[2]].y,vertices[faces[i].vertice_index[2]].z);
                glColor3f(0.55f, 0.45f, 1.0f);
                if(type == GL_QUADS)
                    glVertex3f(vertices[faces[i].vertice_index[3]].x,vertices[faces[i].vertice_index[3]].y,vertices[faces[i].vertice_index[3]].z);
            }
        glEnd();
    }
    else
    {
        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_LINES);
            for(int i = 0;i<face_num;i++)
            {
                for(int j = 0;j<faces[i].vertice_index.size()-1;j++)
                {
                    glVertex3f(vertices[faces[i].vertice_index[j]].x,vertices[faces[i].vertice_index[j]].y,vertices[faces[i].vertice_index[j]].z);
                    glVertex3f(vertices[faces[i].vertice_index[j+1]].x,vertices[faces[i].vertice_index[j+1]].y,vertices[faces[i].vertice_index[j+1]].z);
                }
                glVertex3f(vertices[faces[i].vertice_index[0]].x,vertices[faces[i].vertice_index[0]].y,vertices[faces[i].vertice_index[0]].z);
                glVertex3f(vertices[faces[i].vertice_index[faces[i].vertice_index.size()-1]].x,vertices[faces[i].vertice_index[faces[i].vertice_index.size()-1]].y,vertices[faces[i].vertice_index[faces[i].vertice_index.size()-1]].z);
            }
        glEnd();
    }
}

void GLwidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_F1:
        fullscreen = !fullscreen;
        if (fullscreen)
            showFullScreen();
        else
            showNormal();
        break;
    case Qt::Key_Escape:
        close();
/*    case Qt::Key_L:                                     //L为开启关闭光源的切换键
        m_Light = !m_Light;
        if (m_Light)
        {
            glEnable(GL_LIGHTING);                      //开启光源
        }
        else
        {
            glDisable(GL_LIGHTING);                     //关闭光源
        }
        break;*/
    case Qt::Key_Left:
        y_angle -= 4.0f;
        break;
    case Qt::Key_Right:
        y_angle += 4.0f;
        break;
    case Qt::Key_Up:
        x_angle -= 4.0f;
        break;
    case Qt::Key_Down:
        x_angle += 4.0f;
        break;
    case Qt::Key_Z:
        z_angle += 4.0f;
        break;
    case Qt::Key_X:
        z_angle -= 4.0f;
        break;
    case Qt::Key_1:
        away+=0.2f;
        break;
    case Qt::Key_2:
        away-=0.2f;
        break;
    case Qt::Key_L:
        view_type = !view_type;
        break;
    }
    updateGL();
}


void GLwidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLwidget::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
    GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();
    if (event->buttons() & Qt::LeftButton) {
        x_angle += 180 * dy;
        y_angle += 180 * dx;
        updateGL();
    }
    else if (event->buttons() & Qt::RightButton)
    {
        x_angle += 180 * dy;
        z_angle += 180 * dx;
        updateGL();
    }
    lastPos = event->pos();
}

void GLwidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0){                    // 当滚轮远离使用者时
        away-=0.2f;                // 进行放大
    }else{                                     // 当滚轮向使用者方向旋转时
        away+=0.2f;               // 进行缩小
    }
    updateGL();
}
