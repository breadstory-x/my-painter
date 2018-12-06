#include "rectcontrol.h"

RectControl::RectControl()
{
    currect = NULL;
    press_node = OTHER;
}

RectControl::RectControl(std::vector<Shape*> *all_shape)
{
    currect = NULL;
    press_node = OTHER;
    this->all_shape = all_shape;
}

bool RectControl::isEmpty()
{
    if(all_rectange.size() == 0)
        return true;
    else
        return false;
}

void RectControl::clear_cur()
{
    if(currect != NULL)
        currect = NULL;
}

bool RectControl::is_cur_null()
{
   if(currect != NULL)
       return false;
   else
       return true;
}

void RectControl::scale(double x)
{
    currect->scale(x);
}

void RectControl::onMousePressEvent(QMouseEvent *event)
{
    //判断点击处在直线开始点、结束点、其他位置
    if(currect != NULL && currect->getAngle() == 0
       &&(currect->getStart_one().rx()-10<event->pos().rx() && event->pos().rx()<currect->getStart_one().rx()+10)
       &&(currect->getStart_one().ry()-10<event->pos().ry() && event->pos().ry()<currect->getStart_one().ry()+10))
        press_node = START_ONE;
    else if(currect != NULL && currect->getAngle() == 0
            &&(currect->getStart_two().rx()-10<event->pos().rx() && event->pos().rx()<currect->getStart_two().rx()+10)
            &&(currect->getStart_two().ry()-10<event->pos().ry() && event->pos().ry()<currect->getStart_two().ry()+10))
        press_node = START_TWO;
    else if(currect != NULL && currect->getAngle() == 0
            &&(currect->getStart_three().rx()-10<event->pos().rx() && event->pos().rx()<currect->getStart_three().rx()+10)
            &&(currect->getStart_three().ry()-10<event->pos().ry() && event->pos().ry()<currect->getStart_three().ry()+10))
        press_node = START_THREE;
    else if(currect != NULL && currect->getAngle() == 0
            &&(currect->getStart_four().rx()-10<event->pos().rx() && event->pos().rx()<currect->getStart_four().rx()+10)
            &&(currect->getStart_four().ry()-10<event->pos().ry() && event->pos().ry()<currect->getStart_four().ry()+10))
        press_node = START_FOUR;
    else if(currect != NULL
            &&(currect->getCenter().rx()-10<event->pos().rx() && event->pos().rx()<currect->getCenter().rx()+10)
            &&(currect->getCenter().ry()-10<event->pos().ry() && event->pos().ry()<currect->getCenter().ry()+10))
        press_node = CENTER;
    else if(currect != NULL
            &&(currect->rotatePoint(currect->getCenter(), currect->getRPoint(), currect->getAngle()).rx()-10<event->pos().rx() && event->pos().rx()<currect->rotatePoint(currect->getCenter(), currect->getRPoint(), currect->getAngle()).rx()+10)
            &&(currect->rotatePoint(currect->getCenter(), currect->getRPoint(), currect->getAngle()).ry()-10<event->pos().ry() && event->pos().ry()<currect->rotatePoint(currect->getCenter(), currect->getRPoint(), currect->getAngle()).ry()+10))
        press_node = ROTATE;
    else
    {
        press_node = OTHER;
        currect = new Rectange();
        all_shape->push_back(currect);
        all_rectange.push_back(currect);
        currect->setStart_one(event->pos());
    }
}

void RectControl::onMouseMoveEvent(QMouseEvent *event)
{
    if(press_node == START_ONE)
        currect->setStart_one(event->pos());
    else if(press_node == START_TWO)
    {
        currect->setStart_two(event->pos());
        currect->setStart_one(QPoint(currect->getStart_three().x(),event->pos().y()));
        currect->setStart_four(QPoint(event->pos().x(),currect->getStart_three().y()));
    }
    else if(press_node == START_THREE)
    {
        currect->setStart_three(event->pos());
        currect->setStart_one(QPoint(event->pos().x(),currect->getStart_two().y()));
        currect->setStart_four(QPoint(currect->getStart_two().x(), event->pos().y()));
    }
    else if(press_node == START_FOUR || press_node == OTHER)
        currect->setStart_four(event->pos());
    else if(press_node == CENTER)
        currect->translate(event->pos().x()-currect->getCenter().x(), event->pos().y()-currect->getCenter().y());
    else if(press_node == ROTATE)
    {
        double x = (double)(event->pos().x()-currect->getCenter().x())/(currect->getCenter().y()-event->pos().y());
        if((currect->getCenter().y()-event->pos().y()>=0))
            currect->setAngle(atan(x)*360.0/(2*3.1415926));
        else
            currect->setAngle(180.0 + atan(x)*360.0/(2*3.1415926));
    }
    currect->setOtherPoint();
}

int RectControl::onMousePassiveMoveEvent(QMouseEvent *e)
{
    if( currect != NULL &&
        ((( currect->getAngle() == 0) && (currect->getStart_one().rx()-10<e->pos().rx() && e->pos().rx()<currect->getStart_one().rx()+10)
        &&(currect->getStart_one().ry()-10<e->pos().ry() && e->pos().ry()<currect->getStart_one().ry()+10))
        ||
        (( currect->getAngle() == 0) && (currect->getStart_two().rx()-10<e->pos().rx() && e->pos().rx()<currect->getStart_two().rx()+10)
        &&(currect->getStart_two().ry()-10<e->pos().ry() && e->pos().ry()<currect->getStart_two().ry()+10))
        ||
        (( currect->getAngle() == 0) && (currect->getStart_three().rx()-10<e->pos().rx() && e->pos().rx()<currect->getStart_three().rx()+10)
        &&(currect->getStart_three().ry()-10<e->pos().ry() && e->pos().ry()<currect->getStart_three().ry()+10))
        ||
        (( currect->getAngle() == 0) && (currect->getStart_four().rx()-10<e->pos().rx() && e->pos().rx()<currect->getStart_four().rx()+10)
        &&(currect->getStart_four().ry()-10<e->pos().ry() && e->pos().ry()<currect->getStart_four().ry()+10))
        ||
        ( (currect->getCenter().rx()-10<e->pos().rx() && e->pos().rx()<currect->getCenter().rx()+10)
        &&(currect->getCenter().ry()-10<e->pos().ry() && e->pos().ry()<currect->getCenter().ry()+10))
        ||
        ( (currect->rotatePoint(currect->getCenter(), currect->getRPoint(), currect->getAngle()).rx()-10<e->pos().rx() && e->pos().rx()<currect->rotatePoint(currect->getCenter(), currect->getRPoint(), currect->getAngle()).rx()+10)
        &&(currect->rotatePoint(currect->getCenter(), currect->getRPoint(), currect->getAngle()).ry()-10<e->pos().ry() && e->pos().ry()<currect->rotatePoint(currect->getCenter(), currect->getRPoint(), currect->getAngle()).ry()+10))))
        return 1;
    else
        return 0;
}


