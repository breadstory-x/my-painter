#include "curvecontrol.h"

CurveControl::CurveControl()
{
    curcurve = NULL;
    press_node = OTHER;
    curve_finish = true;
}

CurveControl::CurveControl(std::vector<Shape*> *all_shape)
{
    curcurve = NULL;
    press_node = OTHER;
    curve_finish = true;
    this->all_shape = all_shape;
}

bool CurveControl::isEmpty()
{
    if(all_curve.size() == 0)
        return true;
    else
        return false;
}

void CurveControl::clear_cur()
{
    if(curcurve != NULL)
        curcurve = NULL;
}

bool CurveControl::is_cur_null()
{
   if(curcurve != NULL)
       return false;
   else
       return true;
}

void CurveControl::scale(double x)
{
    curcurve->scale(x);
}

void CurveControl::onMousePressEvent(QMouseEvent *event)
{
    //确定是否编辑
    if(curcurve != NULL && curcurve->getFinish())
    {
        if((curcurve->getCenter().rx()-10<event->pos().rx() && event->pos().rx()<curcurve->getCenter().rx()+10)
         &&(curcurve->getCenter().ry()-10<event->pos().ry() && event->pos().ry()<curcurve->getCenter().ry()+10))
        {
            press_node = CENTER;//平移
            return;
        }
        if(curcurve->getAngle() == 0)
            for(int i = 0;i < curcurve->getCurve_point().size();i++)
            {
                if((curcurve->getCurve_point()[i].rx()-10<event->pos().rx() && event->pos().rx()<curcurve->getCurve_point()[i].rx()+10)
                 &&(curcurve->getCurve_point()[i].ry()-10<event->pos().ry() && event->pos().ry()<curcurve->getCurve_point()[i].ry()+10))
                {
                    press_node = i+1;
                    return;
                }
            }
        if(curcurve != NULL
           &&(curcurve->rotatePoint(curcurve->getCenter(), curcurve->getRPoint(), curcurve->getAngle()).rx()-10<event->pos().rx() && event->pos().rx()<curcurve->rotatePoint(curcurve->getCenter(), curcurve->getRPoint(), curcurve->getAngle()).rx()+10)
           &&(curcurve->rotatePoint(curcurve->getCenter(), curcurve->getRPoint(), curcurve->getAngle()).ry()-10<event->pos().ry() && event->pos().ry()<curcurve->rotatePoint(curcurve->getCenter(), curcurve->getRPoint(), curcurve->getAngle()).ry()+10))
        {
            press_node = ROTATE;//旋转
            return;
        }
    }

    //开始画曲线
    if(curve_finish == true)
    {
        curcurve = new Curve();
        curcurve->setFinish(false);
        curve_finish = false;
        all_shape->push_back(curcurve);
        all_curve.push_back(curcurve);
        if(curcurve->getCurve_point().size() == 0)//没有点的时候多压一点进去，产生刷新效果
            curcurve->getCurve_point().push_back(event->pos());
        curcurve->getCurve_point().push_back(event->pos());
    }
    else if(curcurve->getCurve_point().size() != 0)
    {
        curcurve->getCurve_point().push_back(event->pos());
    }
}
void CurveControl::onMouseMoveEvent(QMouseEvent *event)
{
    if(curcurve->getFinish())
    {
        if(press_node >=1 && press_node <=4)
            curcurve->getCurve_point()[press_node-1] = event->pos();
        else if(press_node == CENTER)
            curcurve->translate(event->pos().x()-curcurve->getCenter().x(), event->pos().y()-curcurve->getCenter().y());
        else if(press_node == ROTATE)
        {
            double x = (double)(event->pos().x()-curcurve->getCenter().x())/(curcurve->getCenter().y()-event->pos().y());
            if((curcurve->getCenter().y()-event->pos().y()>=0))
                curcurve->setAngle(atan(x)*360.0/(2*3.1415926));
            else
                curcurve->setAngle(180.0 + atan(x)*360.0/(2*3.1415926));
        }
        curcurve->setOtherPoint();
    }
    else
        curcurve->getCurve_point()[curcurve->getCurve_point().size()-1] = event->pos();
}
int CurveControl::onMousePassiveMoveEvent(QMouseEvent *e)
{
    if( curcurve != NULL && curcurve->getFinish())//当图形不为空并且已经画完的情况下，可触发编辑鼠标指针
    {
        if(curcurve->getAngle() == 0)
            for(int i = 0;i<curcurve->getCurve_point().size();i++)
                if((curcurve->getCurve_point()[i].rx()-10<e->pos().rx() && e->pos().rx()<curcurve->getCurve_point()[i].rx()+10)
                  &&(curcurve->getCurve_point()[i].ry()-10<e->pos().ry() && e->pos().ry()<curcurve->getCurve_point()[i].ry()+10))
                    return 1;//改变鼠标指针
        if( (curcurve->getCenter().rx()-10<e->pos().rx() && e->pos().rx()<curcurve->getCenter().rx()+10)
        &&(curcurve->getCenter().ry()-10<e->pos().ry() && e->pos().ry()<curcurve->getCenter().ry()+10))
            return 1;
        if( (curcurve->rotatePoint(curcurve->getCenter(), curcurve->getRPoint(), curcurve->getAngle()).rx()-10<e->pos().rx() && e->pos().rx()<curcurve->rotatePoint(curcurve->getCenter(), curcurve->getRPoint(), curcurve->getAngle()).rx()+10)
        &&(curcurve->rotatePoint(curcurve->getCenter(), curcurve->getRPoint(), curcurve->getAngle()).ry()-10<e->pos().ry() && e->pos().ry()<curcurve->rotatePoint(curcurve->getCenter(), curcurve->getRPoint(), curcurve->getAngle()).ry()+10))
            return 1;
    }
    return 0;
}

void CurveControl::onMouseReleaseEvent(QMouseEvent *e)
{
    if(curcurve->getCurve_point().size() == 4)
    {
        curve_finish = true;
        curcurve->setFinish(true);
        curcurve->setOtherPoint();
    }
}
