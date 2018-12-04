#include "circlecontrol.h"

CircleControl::CircleControl()
{
    curcircle = NULL;
    press_node = OTHER;
}

CircleControl::CircleControl(std::vector<Shape*> *all_shape)
{
    curcircle = NULL;
    press_node = OTHER;
    this->all_shape = all_shape;

}

void CircleControl::onMousePressEvent(QMouseEvent *event)
{
    //判断点击处在直线开始点、结束点、其他位置
    if(curcircle != NULL
       &&(curcircle->getStart_one().rx()-10<event->pos().rx() && event->pos().rx()<curcircle->getStart_one().rx()+10)
       &&(curcircle->getStart_one().ry()-10<event->pos().ry() && event->pos().ry()<curcircle->getStart_one().ry()+10))
        press_node = START_ONE;
    else if(curcircle != NULL
            &&(curcircle->getStart_four().rx()-10<event->pos().rx() && event->pos().rx()<curcircle->getStart_four().rx()+10)
            &&(curcircle->getStart_four().ry()-10<event->pos().ry() && event->pos().ry()<curcircle->getStart_four().ry()+10))
        press_node = START_FOUR;
    else if(curcircle != NULL
            &&(curcircle->getCenter().rx()-10<event->pos().rx() && event->pos().rx()<curcircle->getCenter().rx()+10)
            &&(curcircle->getCenter().ry()-10<event->pos().ry() && event->pos().ry()<curcircle->getCenter().ry()+10))
        press_node = CENTER;
    else
    {
        press_node = OTHER;
        curcircle = new Circle();
        all_shape->push_back(curcircle);
        curcircle->setStart_one(event->pos());
    }
}

void CircleControl::onMouseMoveEvent(QMouseEvent *event)
{
    if(press_node == START_ONE)
        curcircle->setStart_one(event->pos());
    else if(press_node == START_TWO)
    {
        curcircle->setStart_two(event->pos());
        curcircle->setStart_one(QPoint(curcircle->getStart_three().x(),event->pos().y()));
        curcircle->setStart_four(QPoint(event->pos().x(),curcircle->getStart_three().y()));
    }
    else if(press_node == START_THREE)
    {
        curcircle->setStart_three(event->pos());
        curcircle->setStart_one(QPoint(event->pos().x(),curcircle->getStart_two().y()));
        curcircle->setStart_four(QPoint(curcircle->getStart_two().x(), event->pos().y()));
    }
    else if(press_node == START_FOUR)
        curcircle->setStart_four(event->pos());
    else if(press_node == OTHER)
    {
        curcircle->setStart_four(event->pos());
        /*int r = abs((curcircle->getStart_one().y() - curcircle->getStart_four().y())/2)>abs((curcircle->getStart_one().x() - curcircle->getStart_four().x())/2)?abs((curcircle->getStart_one().y() - curcircle->getStart_four().y())/2):abs((curcircle->getStart_one().x() - curcircle->getStart_four().x())/2);//半径
        if((curcircle->getStart_one().x()+2*r == curcircle->getStart_four().x() || curcircle->getStart_one().x()-2*r == curcircle->getStart_four().x()) && curcircle->getStart_four().y() > curcircle->getStart_one().y())
            curcircle->getStart_four().setY(curcircle->getStart_one().y()+2*r);
        else if((curcircle->getStart_one().x()+2*r == curcircle->getStart_four().x() || curcircle->getStart_one().x()-2*r == curcircle->getStart_four().x())&& curcircle->getStart_four().y() < curcircle->getStart_one().y())
            curcircle->getStart_four().setY(curcircle->getStart_one().y()-2*r);
        else if((curcircle->getStart_one().y()+2*r == curcircle->getStart_four().y() || curcircle->getStart_one().y()-2*r == curcircle->getStart_four().y()) && curcircle->getStart_four().x() > curcircle->getStart_one().x())
            curcircle->getStart_four().setX(curcircle->getStart_one().x()+2*r);
        else if((curcircle->getStart_one().y()+2*r == curcircle->getStart_four().y() || curcircle->getStart_one().y()-2*r == curcircle->getStart_four().y()) && curcircle->getStart_four().x() < curcircle->getStart_one().x())
            curcircle->getStart_four().setX(curcircle->getStart_one().x()-2*r);*/
    }
    else if(press_node == CENTER)
        curcircle->translate(event->pos().x()-curcircle->getCenter().x(), event->pos().y()-curcircle->getCenter().y());
    curcircle->setOtherPoint();
}
