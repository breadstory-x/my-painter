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
    else if(curline != NULL && curline->getAngle() == 0
            &&(curline->getCenter().rx()-10<event->pos().rx() && event->pos().rx()<curline->getCenter().rx()+10)
            &&(curline->getCenter().ry()-10<event->pos().ry() && event->pos().ry()<curline->getCenter().ry()+10))
        press_node = CENTER;
    else if(curline != NULL
            &&(curline->getRPoint().rx()-10<event->pos().rx() && event->pos().rx()<curline->getRPoint().rx()+10)
            &&(curline->getRPoint().ry()-10<event->pos().ry() && event->pos().ry()<curline->getRPoint().ry()+10))
        press_node = ROTATE;
    else
    {
        press_node = OTHER;
        curline = new Line();
        all_shape->push_back(curline);
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
        double x = (double)(event->pos().x()-curline->getCenter().x())/(curline->getCenter().y()-event->pos().y());
        curline->setAngle(atan(x)*360.0/(2*3.1415926));
    }
    curline->setOtherPoint();
}

int LineControl::onMousePassiveMoveEvent(QMouseEvent *e)
{
    if( curline != NULL && curline->getAngle() == 0 &&
        (( (curline->getStart().rx()-10<e->pos().rx() && e->pos().rx()<curline->getStart().rx()+10)
        &&(curline->getStart().ry()-10<e->pos().ry() && e->pos().ry()<curline->getStart().ry()+10))
        ||
        ( (curline->getEnd().rx()-10<e->pos().rx() && e->pos().rx()<curline->getEnd().rx()+10)
        &&(curline->getEnd().ry()-10<e->pos().ry() && e->pos().ry()<curline->getEnd().ry()+10))
        ||
        ( (curline->getCenter().rx()-10<e->pos().rx() && e->pos().rx()<curline->getCenter().rx()+10)
        &&(curline->getCenter().ry()-10<e->pos().ry() && e->pos().ry()<curline->getCenter().ry()+10))
        ||
        ( (curline->getRPoint().rx()-10<e->pos().rx() && e->pos().rx()<curline->getRPoint().rx()+10)
        &&(curline->getRPoint().ry()-10<e->pos().ry() && e->pos().ry()<curline->getRPoint().ry()+10)) ))
        return 1;
    else
        return 0;
}
