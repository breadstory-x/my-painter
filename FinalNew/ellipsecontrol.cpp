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

void EllipseControl::onMousePressEvent(QMouseEvent *event)
{
    //判断点击处在直线开始点、结束点、其他位置
    if(curellipse != NULL
       &&(curellipse->getStart_one().rx()-10<event->pos().rx() && event->pos().rx()<curellipse->getStart_one().rx()+10)
       &&(curellipse->getStart_one().ry()-10<event->pos().ry() && event->pos().ry()<curellipse->getStart_one().ry()+10))
        press_node = START_ONE;
    else if(curellipse != NULL
            &&(curellipse->getStart_two().rx()-10<event->pos().rx() && event->pos().rx()<curellipse->getStart_two().rx()+10)
            &&(curellipse->getStart_two().ry()-10<event->pos().ry() && event->pos().ry()<curellipse->getStart_two().ry()+10))
        press_node = START_TWO;
    else if(curellipse != NULL
            &&(curellipse->getStart_three().rx()-10<event->pos().rx() && event->pos().rx()<curellipse->getStart_three().rx()+10)
            &&(curellipse->getStart_three().ry()-10<event->pos().ry() && event->pos().ry()<curellipse->getStart_three().ry()+10))
        press_node = START_THREE;
    else if(curellipse != NULL
            &&(curellipse->getStart_four().rx()-10<event->pos().rx() && event->pos().rx()<curellipse->getStart_four().rx()+10)
            &&(curellipse->getStart_four().ry()-10<event->pos().ry() && event->pos().ry()<curellipse->getStart_four().ry()+10))
        press_node = START_FOUR;
    else if(curellipse != NULL
            &&(curellipse->getCenter().rx()-10<event->pos().rx() && event->pos().rx()<curellipse->getCenter().rx()+10)
            &&(curellipse->getCenter().ry()-10<event->pos().ry() && event->pos().ry()<curellipse->getCenter().ry()+10))
        press_node = CENTER;
    else if(curellipse != NULL
            &&(curellipse->getRPoint().rx()-10<event->pos().rx() && event->pos().rx()<curellipse->getRPoint().rx()+10)
            &&(curellipse->getRPoint().ry()-10<event->pos().ry() && event->pos().ry()<curellipse->getRPoint().ry()+10))
        press_node = ROTATE;
    else
    {
        press_node = OTHER;
        curellipse = new Ellipse();
        all_shape->push_back(curellipse);
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
        curellipse->setAngle(atan(x)*360.0/(2*3.1415926));
    }
    curellipse->setOtherPoint();
}

int EllipseControl::onMousePassiveMoveEvent(QMouseEvent *e)
{
    if( curellipse != NULL &&
        (( (curellipse->getStart_one().rx()-10<e->pos().rx() && e->pos().rx()<curellipse->getStart_one().rx()+10)
        &&(curellipse->getStart_one().ry()-10<e->pos().ry() && e->pos().ry()<curellipse->getStart_one().ry()+10))
        ||
        ( (curellipse->getStart_two().rx()-10<e->pos().rx() && e->pos().rx()<curellipse->getStart_two().rx()+10)
        &&(curellipse->getStart_two().ry()-10<e->pos().ry() && e->pos().ry()<curellipse->getStart_two().ry()+10))
        ||
        ( (curellipse->getStart_three().rx()-10<e->pos().rx() && e->pos().rx()<curellipse->getStart_three().rx()+10)
        &&(curellipse->getStart_three().ry()-10<e->pos().ry() && e->pos().ry()<curellipse->getStart_three().ry()+10))
        ||
        ( (curellipse->getStart_four().rx()-10<e->pos().rx() && e->pos().rx()<curellipse->getStart_four().rx()+10)
        &&(curellipse->getStart_four().ry()-10<e->pos().ry() && e->pos().ry()<curellipse->getStart_four().ry()+10))
        ||
        ( (curellipse->getCenter().rx()-10<e->pos().rx() && e->pos().rx()<curellipse->getCenter().rx()+10)
        &&(curellipse->getCenter().ry()-10<e->pos().ry() && e->pos().ry()<curellipse->getCenter().ry()+10))
        ||
        ( (curellipse->getRPoint().rx()-10<e->pos().rx() && e->pos().rx()<curellipse->getRPoint().rx()+10)
        &&(curellipse->getRPoint().ry()-10<e->pos().ry() && e->pos().ry()<curellipse->getRPoint().ry()+10))))
        return 1;
    else
        return 0;
}
