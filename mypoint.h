#ifndef MYPOINT_H
#define MYPOINT_H

#include "boost/graph/graph_traits.hpp"
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>

class mypoint: public QWidget, public QGraphicsEllipseItem
{
    Q_OBJECT


public:
    explicit mypoint(QWidget *parent = 0);

    QPointF currentpos;                                    //position in map coordinates that changes with motion
    QPointF defpos;                                        //default position in map coordinates
    QPointF buffer;                                        //point variable needed to compensate distortions of scenepos made by scaling
    QGraphicsTextItem* text = new QGraphicsTextItem(this); //vertex text (number)
    QColor color;                                          //color chosen on tab (NOT current brush of the item)
    QColor tempcol;                                        //current brush of the item (is needed only to return to it after edging)

    int mode;                                              //current mode
    bool edging;                                           //variable responsible for current status of adding an edge
    int num;                                               //number of a vertex


protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent* c);

    void changemode(int);
    void changecolor(int c);
    void pan_edging_started();
    void pan_edging_finished();
    void set_rad(int r);
    void num_decrease(int n);

signals:
    void removepoint(mypoint* p);
    void edge_begin(mypoint* p);
    void edge_end(mypoint* p);
    void pointmove(mypoint* p);


};

#endif // MYPOINT_H
