#ifndef MYLINE_H
#define MYLINE_H

#include "mypoint.h"
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QPen>

class myline: public QWidget, public QGraphicsLineItem
{
    Q_OBJECT

public:
    explicit  myline(QWidget *parent = 0);
    QGraphicsTextItem* text = new QGraphicsTextItem(this); //text anchored to the center of the edge (default is "1")
    mypoint* pt1;                                          //pointer to first vertex of the edge
    mypoint* pt2;                                          //pointer to seccond vertex of the edge
    int mode;                                              //current mode
    QColor color;                                          //color chosen on the tab (NOT the current brush of item)

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent* e);
    void changelincolor(int c);

    void removenode(mypoint* p);
    void move(mypoint* p);
    void changemode(int);
    void edge_permit_l(mypoint* p1, mypoint* p2);
    void set_width(int r);

signals:
    void removeline(myline* l);
    void removeline_node(myline *l);
    void edge_draw_l(int m);

private:

};

#endif // MYLINE_H
