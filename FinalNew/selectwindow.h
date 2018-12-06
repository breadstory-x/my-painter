#ifndef SELCETWINDOW_H
#define SELCETWINDOW_H
#include<QPoint>
#include<QPainter>

class SelectWindow
{
public:
    SelectWindow();
    void paint(QPainter *painter);

    void setStart(QPoint s){ start = s; }
    void setEnd(QPoint e){ end = e; }
    QPoint getStart(){ return start; }
    QPoint getEnd(){ return end; }

private:
    QPoint start;
    QPoint end;
};

#endif // SELCETWINDOW_H
