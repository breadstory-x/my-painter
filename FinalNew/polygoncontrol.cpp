#include "polygoncontrol.h"

PolygonControl::PolygonControl()
{
    curpolygon = NULL;
    press_node = -1;
    polygon_finish = true;
}

PolygonControl::PolygonControl(std::vector<Shape*> *all_shape)
{
    curpolygon = NULL;
    press_node = -1;
    polygon_finish = true;
    this->all_shape = all_shape;
}

bool PolygonControl::isEmpty()
{
    if(all_polygon.size() == 0)
        return true;
    else
        return false;
}

void PolygonControl::clear_cur()
{
    if(curpolygon != NULL)
        curpolygon = NULL;
}

bool PolygonControl::is_cur_null()
{
   if(curpolygon != NULL)
       return false;
   else
       return true;
}

void PolygonControl::scale(double x)
{
    curpolygon->scale(x);
}

void PolygonControl::onMousePressEvent(QMouseEvent *event)
{
    //判断点击处在直线开始点、结束点、其他位置
    if(curpolygon != NULL && curpolygon->getFinish())
    {
        if((curpolygon->getCenter().rx()-10<event->pos().rx() && event->pos().rx()<curpolygon->getCenter().rx()+10)
         &&(curpolygon->getCenter().ry()-10<event->pos().ry() && event->pos().ry()<curpolygon->getCenter().ry()+10))
        {
            press_node = -2;//平移
            return;
        }
        if(curpolygon->getAngle() == 0)
            for(int i = 0;i < curpolygon->getPoly_point().size();i++)
            {
                if((curpolygon->getPoly_point()[i].rx()-10<event->pos().rx() && event->pos().rx()<curpolygon->getPoly_point()[i].rx()+10)
                 &&(curpolygon->getPoly_point()[i].ry()-10<event->pos().ry() && event->pos().ry()<curpolygon->getPoly_point()[i].ry()+10))
                {
                    press_node = i;
                    return;
                }
            }
        if(curpolygon != NULL
           &&(curpolygon->rotatePoint(curpolygon->getCenter(), curpolygon->getRPoint(), curpolygon->getAngle()).rx()-10<event->pos().rx() && event->pos().rx()<curpolygon->rotatePoint(curpolygon->getCenter(), curpolygon->getRPoint(), curpolygon->getAngle()).rx()+10)
           &&(curpolygon->rotatePoint(curpolygon->getCenter(), curpolygon->getRPoint(), curpolygon->getAngle()).ry()-10<event->pos().ry() && event->pos().ry()<curpolygon->rotatePoint(curpolygon->getCenter(), curpolygon->getRPoint(), curpolygon->getAngle()).ry()+10))
        {
            press_node = -3;//旋转
            return;
        }
    }
    if(event->button() == Qt::LeftButton)
    {
        if(polygon_finish == true)
        {
            curpolygon = new Polygon();
            curpolygon->setFinish(false);
            polygon_finish = false;
            all_shape->push_back(curpolygon);
            all_polygon.push_back(curpolygon);
            if(curpolygon->getPoly_point().size() == 0)//没有点的时候多压一点进去，产生刷新效果
                curpolygon->getPoly_point().push_back(event->pos());
            curpolygon->getPoly_point().push_back(event->pos());

        }
        else if(curpolygon->getPoly_point().size() != 0)
        {
            curpolygon->getPoly_point().push_back(event->pos());
        }

    }
    else if(event->button() == Qt::RightButton)
    {
        if(curpolygon->getPoly_point().size() != 0)
        {
            polygon_finish = true;
            curpolygon->setFinish(true);
            curpolygon->setOtherPoint();
        }
    }

}

void PolygonControl::onMouseMoveEvent(QMouseEvent *event)
{
    if(curpolygon->getFinish())
    {
        if(press_node >=0)
            curpolygon->getPoly_point()[press_node] = event->pos();
        else if(press_node == -2)
            curpolygon->translate(event->pos().x()-curpolygon->getCenter().x(), event->pos().y()-curpolygon->getCenter().y());
        else if(press_node == -3)
        {
            double x = (double)(event->pos().x()-curpolygon->getCenter().x())/(curpolygon->getCenter().y()-event->pos().y());
            if((curpolygon->getCenter().y()-event->pos().y()>=0))
                curpolygon->setAngle(atan(x)*360.0/(2*3.1415926));
            else
                curpolygon->setAngle(180.0 + atan(x)*360.0/(2*3.1415926));

        }
        curpolygon->setOtherPoint();
    }
    else
    {
        curpolygon->getPoly_point()[curpolygon->getPoly_point().size()-1] = event->pos();
    }
}

int PolygonControl::onMousePassiveMoveEvent(QMouseEvent *e)
{
    if( curpolygon != NULL && curpolygon->getFinish())
    {
        if(curpolygon->getAngle() == 0)
            for(int i = 0;i<curpolygon->getPoly_point().size();i++)
                if((curpolygon->getPoly_point()[i].rx()-10<e->pos().rx() && e->pos().rx()<curpolygon->getPoly_point()[i].rx()+10)
                  &&(curpolygon->getPoly_point()[i].ry()-10<e->pos().ry() && e->pos().ry()<curpolygon->getPoly_point()[i].ry()+10))
                    return 1;//改变鼠标指针
        if( (curpolygon->getCenter().rx()-10<e->pos().rx() && e->pos().rx()<curpolygon->getCenter().rx()+10)
        &&(curpolygon->getCenter().ry()-10<e->pos().ry() && e->pos().ry()<curpolygon->getCenter().ry()+10))
            return 1;
        if( (curpolygon->rotatePoint(curpolygon->getCenter(), curpolygon->getRPoint(), curpolygon->getAngle()).rx()-10<e->pos().rx() && e->pos().rx()<curpolygon->rotatePoint(curpolygon->getCenter(), curpolygon->getRPoint(), curpolygon->getAngle()).rx()+10)
        &&(curpolygon->rotatePoint(curpolygon->getCenter(), curpolygon->getRPoint(), curpolygon->getAngle()).ry()-10<e->pos().ry() && e->pos().ry()<curpolygon->rotatePoint(curpolygon->getCenter(), curpolygon->getRPoint(), curpolygon->getAngle()).ry()+10))
            return 1;
    }
    return 0;
}
