#include "myline.h"

myline::myline(QWidget* parent) :
    QWidget(parent), QGraphicsLineItem()
{
    mode = 0;
    setZValue(-1);                                         // so the verticies are always above edges

    //signals recieved from panel
    connect(parent,SIGNAL(setmode(int)),this,SLOT(changemode(int)));
    connect(parent, SIGNAL(setcolor(int)), this, SLOT(changelincolor(int)));
    connect(parent, SIGNAL(removenode(mypoint*)), this, SLOT(removenode(mypoint*)));
    connect(parent, SIGNAL(lmv(mypoint*)), this, SLOT(move(mypoint*)));
    connect(parent, SIGNAL(edge_permit(mypoint*,mypoint*)), this, SLOT(edge_permit_l(mypoint*,mypoint*)));
    connect(parent, SIGNAL(set_rad(int)), this, SLOT(set_width(int)));

    //signals send to panel
    connect(this, SIGNAL(edge_draw_l(int)), parent, SLOT(edge_draw(int)));
    connect(this, SIGNAL(removeline(myline*)), parent, SLOT(rml(myline*)));
    connect(this, SIGNAL(removeline_node(myline*)), parent, SLOT(rml_node(myline*)));
}

void myline::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (mode == 2 && e->buttons() == Qt::LeftButton)       // mode 2 - remove
    {
        emit removeline(this);
    }
    if (mode == 5)                                         // mode 5 - colorization
    {
        QPen pn;
        pn.setWidth(this->pen().width());
        pn.setBrush(color);
        this->setPen(pn);
    }
}

void myline::changelincolor(int c)
{
    if (c == 1) this->color = QColor(Qt::gray);
    if (c == 2) this->color = QColor(Qt::red);
    if (c == 3) this->color = QColor(Qt::yellow);
    if (c == 4) this->color = QColor(Qt::green);
}

void myline::removenode(mypoint *p)                        //remove edges adjacent to vertex p
{
    if (p == pt1 || p == pt2)
        //if (exists)
        {
            //this->exists = false;
            emit removeline_node(this);
        }
}

void myline::move(mypoint* p)                              //move edges adjacent to vertex p
{
    if (p == pt1)
    {
        this->setLine(p->currentpos.x(), p->currentpos.y(), line().x2(), line().y2());
        this->text->setPos(p->currentpos.x() / 2.0 + line().x2() / 2.0 - 10, p->currentpos.y() / 2.0 + line().y2() / 2.0 - 20);
    }
    if (p == pt2)
    {
        this->setLine(line().x1(), line().y1(), p->currentpos.x(), p->currentpos.y());
        this->text->setPos(p->currentpos.x() / 2.0 + line().x1() / 2.0 - 10, p->currentpos.y() / 2.0 + line().y1() / 2.0 - 20);
    }
}

void myline::changemode(int m)
{
    mode = m;
}

void myline::edge_permit_l(mypoint* p1, mypoint* p2)       //check if there is already an edge between verticies p1 and p2 to prevent parallel edges
{
    if ((pt1 == p1 && pt2 == p2) || (pt1 == p2 && pt2 == p1)) emit edge_draw_l(0);
    else emit edge_draw_l(1);
}

void myline::set_width(int r)                              //set width corresponding to current vertex radius
{
    QPen pen;
    pen.setWidth(2 + trunc(r/8.0));
    pen.setBrush(this->pen().brush());
    this->setPen(pen);
    this->text->setFont(QFont("Times", r));
}
