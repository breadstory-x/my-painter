#include "linecontrol.h"

LineControl::LineControl()
{
    curline = NULL;
    press_node = OTHER;
}

LineControl::LineControl(std::vector<Shape*> *all_shape)
{
    curline = NULL;
    this->all_shape = all_shape;
    press_node = OTHER;
}

bool LineControl::isEmpty()
{
    if(all_line.size() == 0)
        return true;
    else
        return false;
}

void LineControl::clear_cur()
{
    if(curline != NULL)
        curline = NULL;
}

bool LineControl::is_cur_null()
{
   if(curline != NULL)
       return false;
   else
       return true;
}

void LineControl::scale(double x)
{
    curline->scale(x);
}

void LineControl::cut(SelectWindow *sw)
{
    if(curline == NULL)
    {
        QMessageBox::information(NULL,  u8"Error!", u8"请先画直线，再进行裁剪！");
        return;
    }
    //TODO:直线裁剪算法,梁友栋
    bool flag = false;
    float u1 = 0, u2 = 1, r;
    int p[4],q[4];
    //判断裁剪框的范围
    int xmin = sw->getStart().x()<sw->getEnd().x()?sw->getStart().x():sw->getEnd().x();
    int xmax = sw->getStart().x()>sw->getEnd().x()?sw->getStart().x():sw->getEnd().x();
    int ymin = sw->getStart().y()<sw->getEnd().y()?sw->getStart().y():sw->getEnd().y();
    int ymax = sw->getStart().y()>sw->getEnd().y()?sw->getStart().y():sw->getEnd().y();

    p[0] = curline->getStart().x()-curline->getEnd().x(); //-△x
    p[1] = -p[0];                                         //△x
    p[2] = curline->getStart().y()-curline->getEnd().y(); //-△y
    p[3] = -p[2];                                         //△y

    q[0] = curline->getStart().x() - xmin;  //x1-xmin
    q[1] = xmax - curline->getStart().x();  //xmax-x1
    q[2] = curline->getStart().y() - ymin;  //y1-ymin
    q[3] = ymax - curline->getStart().y();  //ymax-y1

    for(int i = 0; i < 4; i++)
    {
        r = (float)q[i] / (float)p[i];
        if(p[i] < 0)
        {
            u1 = u1>r?u1:r;
            if(u1 > u2)
            {
                flag = true;
            }
        }
        if(p[i] > 0)
        {
            u2 = u2<r?u2:r;
            if(u1 > u2)
            {
                flag = true;
            }
        }
        if(p[i] == 0 && q[i] < 0)
            flag = true;
    }
    if(flag)
    {
        all_line.pop_back();
        all_shape->pop_back();
        delete curline;
        return;
    }
    //将交点作为起止点赋给裁剪后的直线
    QPoint tempstart(curline->getStart().x() - u1*(curline->getStart().x()-curline->getEnd().x()),curline->getStart().y() - u1*(curline->getStart().y()-curline->getEnd().y()));
    QPoint tempend(curline->getStart().x() - u2*(curline->getStart().x()-curline->getEnd().x()),curline->getStart().y() - u2*(curline->getStart().y()-curline->getEnd().y()));
    curline->setStart(tempstart);
    curline->setEnd(tempend);

    curline->setOtherPoint();
}
void LineControl::onMousePressEvent(QMouseEvent *event)
{
    //判断点击处在直线开始点、结束点、其他位置
    if(curline != NULL && curline->getAngle() == 0
       &&(curline->getStart().rx()-10<event->pos().rx() && event->pos().rx()<curline->getStart().rx()+10)
       &&(curline->getStart().ry()-10<event->pos().ry() && event->pos().ry()<curline->getStart().ry()+10))
        press_node = START_ONE;
    else if(curline != NULL && curline->getAngle() == 0
            &&(curline->getEnd().rx()-10<event->pos().rx() && event->pos().rx()<curline->getEnd().rx()+10)
            &&(curline->getEnd().ry()-10<event->pos().ry() && event->pos().ry()<curline->getEnd().ry()+10))
        press_node = START_FOUR;
    else if(curline != NULL
            &&(curline->getCenter().rx()-10<event->pos().rx() && event->pos().rx()<curline->getCenter().rx()+10)
            &&(curline->getCenter().ry()-10<event->pos().ry() && event->pos().ry()<curline->getCenter().ry()+10))
        press_node = CENTER;
    else if(curline != NULL
            &&(curline->rotatePoint(curline->getCenter(), curline->getRPoint(), curline->getAngle()).rx()-10<event->pos().rx() && event->pos().rx()<curline->rotatePoint(curline->getCenter(), curline->getRPoint(), curline->getAngle()).rx()+10)
            &&(curline->rotatePoint(curline->getCenter(), curline->getRPoint(), curline->getAngle()).ry()-10<event->pos().ry() && event->pos().ry()<curline->rotatePoint(curline->getCenter(), curline->getRPoint(), curline->getAngle()).ry()+10))
        press_node = ROTATE;
    else
    {
        press_node = OTHER;
        curline = new Line();
        all_shape->push_back(curline);
        all_line.push_back(curline);
        curline->setStart(event->pos());
    }
}

void LineControl::onMouseMoveEvent(QMouseEvent *event)
{
    if(press_node == START_ONE)
        curline->setStart(event->pos());
    else if(press_node == START_FOUR || press_node == OTHER)
        curline->setEnd(event->pos());
    else if(press_node == CENTER)
        curline->translate(event->pos().x()-curline->getCenter().x(), event->pos().y()-curline->getCenter().y());
    else if(press_node == ROTATE)
    {
        double x = (double)(event->pos().x()-curline->getCenter().x())/(curline->getCenter().y()-event->pos().y());//鼠标位置与中心点和垂直线的角度
        double y = (double)(curline->getRPoint().x()-curline->getCenter().x())/(curline->getCenter().y()-curline->getRPoint().y());//旋转点与中心点的角度
        if((curline->getCenter().y()-event->pos().y()>=0))
            curline->setAngle((atan(x)-atan(y))*360.0/(2*3.1415926));
        else
            curline->setAngle(180.0 + (atan(x)-atan(y))*360.0/(2*3.1415926));

    }
    curline->setOtherPoint();
}

int LineControl::onMousePassiveMoveEvent(QMouseEvent *e)
{
    if( curline != NULL &&
        ((curline->getAngle() == 0 && (curline->getStart().rx()-10<e->pos().rx() && e->pos().rx()<curline->getStart().rx()+10)
        &&(curline->getStart().ry()-10<e->pos().ry() && e->pos().ry()<curline->getStart().ry()+10))
        ||
        (curline->getAngle() == 0 && (curline->getEnd().rx()-10<e->pos().rx() && e->pos().rx()<curline->getEnd().rx()+10)
        &&(curline->getEnd().ry()-10<e->pos().ry() && e->pos().ry()<curline->getEnd().ry()+10))
        ||
        ( (curline->getCenter().rx()-10<e->pos().rx() && e->pos().rx()<curline->getCenter().rx()+10)
        &&(curline->getCenter().ry()-10<e->pos().ry() && e->pos().ry()<curline->getCenter().ry()+10))
        ||
        ( (curline->rotatePoint(curline->getCenter(), curline->getRPoint(), curline->getAngle()).rx()-10<e->pos().rx() && e->pos().rx()<curline->rotatePoint(curline->getCenter(), curline->getRPoint(), curline->getAngle()).rx()+10)
        &&(curline->rotatePoint(curline->getCenter(), curline->getRPoint(), curline->getAngle()).ry()-10<e->pos().ry() && e->pos().ry()<curline->rotatePoint(curline->getCenter(), curline->getRPoint(), curline->getAngle()).ry()+10)) ))
        return 1;
    else
        return 0;
}
