#include "ellipsecontrol.h"

EllipseControl::EllipseControl()
{
    curellipse = NULL;
    press_node = OTHER;
}

EllipseControl::EllipseControl(std::vector<Shape*> *all_shape)
{
    curellipse = NULL;
    press_node = OTHER;
    this->all_shape = all_shape;
}

bool EllipseControl::isEmpty()
{
    if(all_ellipse.size() == 0)
        return true;
    else
        return false;
}

void EllipseControl::clear_cur()
{
    if(curellipse != NULL)
        curellipse = NULL;
}

bool EllipseControl::is_cur_null()
{
   if(curellipse != NULL)
       return false;
   else
       return true;
}

void EllipseControl::scale(double x)
{
    curellipse->scale(x);
}

void EllipseControl::onMousePressEvent(QMouseEvent *event)
{
    //判断点击处在控制点
    if(curellipse != NULL && curellipse->getAngle()==0
       &&(curellipse->getStart_one().rx()-10<event->pos().rx() && event->pos().rx()<curellipse->getStart_one().rx()+10)
       &&(curellipse->getStart_one().ry()-10<event->pos().ry() && event->pos().ry()<curellipse->getStart_one().ry()+10))
        press_node = START_ONE;
    else if(curellipse != NULL && curellipse->getAngle()==0
            &&(curellipse->getStart_two().rx()-10<event->pos().rx() && event->pos().rx()<curellipse->getStart_two().rx()+10)
            &&(curellipse->getStart_two().ry()-10<event->pos().ry() && event->pos().ry()<curellipse->getStart_two().ry()+10))
        press_node = START_TWO;
    else if(curellipse != NULL && curellipse->getAngle()==0
            &&(curellipse->getStart_three().rx()-10<event->pos().rx() && event->pos().rx()<curellipse->getStart_three().rx()+10)
            &&(curellipse->getStart_three().ry()-10<event->pos().ry() && event->pos().ry()<curellipse->getStart_three().ry()+10))
        press_node = START_THREE;
    else if(curellipse != NULL && curellipse->getAngle()==0
            &&(curellipse->getStart_four().rx()-10<event->pos().rx() && event->pos().rx()<curellipse->getStart_four().rx()+10)
            &&(curellipse->getStart_four().ry()-10<event->pos().ry() && event->pos().ry()<curellipse->getStart_four().ry()+10))
        press_node = START_FOUR;
    else if(curellipse != NULL
            &&(curellipse->getCenter().rx()-10<event->pos().rx() && event->pos().rx()<curellipse->getCenter().rx()+10)
            &&(curellipse->getCenter().ry()-10<event->pos().ry() && event->pos().ry()<curellipse->getCenter().ry()+10))
        press_node = CENTER;
    else if(curellipse != NULL
            &&(curellipse->rotatePoint(curellipse->getCenter(), curellipse->getRPoint(), curellipse->getAngle()).rx()-10<event->pos().rx() && event->pos().rx()<curellipse->rotatePoint(curellipse->getCenter(), curellipse->getRPoint(), curellipse->getAngle()).rx()+10)
            &&(curellipse->rotatePoint(curellipse->getCenter(), curellipse->getRPoint(), curellipse->getAngle()).ry()-10<event->pos().ry() && event->pos().ry()<curellipse->rotatePoint(curellipse->getCenter(), curellipse->getRPoint(), curellipse->getAngle()).ry()+10))
        press_node = ROTATE;//判断是否在旋转后的控制点，主要是为了继续旋转
    else
    {
        press_node = OTHER;
        curellipse = new Ellipse();
        all_shape->push_back(curellipse);
        all_ellipse.push_back(curellipse);
        curellipse->setStart_one(event->pos());
    }
}

void EllipseControl::onMouseMoveEvent(QMouseEvent *event)
{
    if(press_node == START_ONE)
        curellipse->setStart_one(event->pos());
    else if(press_node == START_TWO)
    {
        curellipse->setStart_two(event->pos());
        curellipse->setStart_one(QPoint(curellipse->getStart_three().x(),event->pos().y()));
        curellipse->setStart_four(QPoint(event->pos().x(),curellipse->getStart_three().y()));
    }
    else if(press_node == START_THREE)
    {
        curellipse->setStart_three(event->pos());
        curellipse->setStart_one(QPoint(event->pos().x(),curellipse->getStart_two().y()));
        curellipse->setStart_four(QPoint(curellipse->getStart_two().x(), event->pos().y()));
    }
    else if(press_node == START_FOUR || press_node == OTHER)
        curellipse->setStart_four(event->pos());
    else if(press_node == CENTER)
        curellipse->translate(event->pos().x()-curellipse->getCenter().x(), event->pos().y()-curellipse->getCenter().y());
    else if(press_node == ROTATE)
    {
        double x = (double)(event->pos().x()-curellipse->getCenter().x())/(curellipse->getCenter().y()-event->pos().y());
        if((curellipse->getCenter().y()-event->pos().y()>=0))
            curellipse->setAngle(atan(x)*360.0/(2*3.1415926));
        else
            curellipse->setAngle(180.0 + atan(x)*360.0/(2*3.1415926));
    }
    curellipse->setOtherPoint();
}

int EllipseControl::onMousePassiveMoveEvent(QMouseEvent *e)
{
    if( curellipse != NULL &&
        (((curellipse->getAngle()==0) && (curellipse->getStart_one().rx()-10<e->pos().rx() && e->pos().rx()<curellipse->getStart_one().rx()+10)
        &&(curellipse->getStart_one().ry()-10<e->pos().ry() && e->pos().ry()<curellipse->getStart_one().ry()+10))
        ||
        ((curellipse->getAngle()==0) && (curellipse->getStart_two().rx()-10<e->pos().rx() && e->pos().rx()<curellipse->getStart_two().rx()+10)
        &&(curellipse->getStart_two().ry()-10<e->pos().ry() && e->pos().ry()<curellipse->getStart_two().ry()+10))
        ||
        ((curellipse->getAngle()==0) && (curellipse->getStart_three().rx()-10<e->pos().rx() && e->pos().rx()<curellipse->getStart_three().rx()+10)
        &&(curellipse->getStart_three().ry()-10<e->pos().ry() && e->pos().ry()<curellipse->getStart_three().ry()+10))
        ||
        ((curellipse->getAngle()==0) && (curellipse->getStart_four().rx()-10<e->pos().rx() && e->pos().rx()<curellipse->getStart_four().rx()+10)
        &&(curellipse->getStart_four().ry()-10<e->pos().ry() && e->pos().ry()<curellipse->getStart_four().ry()+10))
        ||
        ( (curellipse->getCenter().rx()-10<e->pos().rx() && e->pos().rx()<curellipse->getCenter().rx()+10)
        &&(curellipse->getCenter().ry()-10<e->pos().ry() && e->pos().ry()<curellipse->getCenter().ry()+10))
        ||
        ( (curellipse->rotatePoint(curellipse->getCenter(), curellipse->getRPoint(), curellipse->getAngle()).rx()-10<e->pos().rx() && e->pos().rx()<curellipse->rotatePoint(curellipse->getCenter(), curellipse->getRPoint(), curellipse->getAngle()).rx()+10)
        &&(curellipse->rotatePoint(curellipse->getCenter(), curellipse->getRPoint(), curellipse->getAngle()).ry()-10<e->pos().ry() && e->pos().ry()<curellipse->rotatePoint(curellipse->getCenter(), curellipse->getRPoint(), curellipse->getAngle()).ry()+10))))
        return 1;
    else
        return 0;
}
