#include "panel.h"
#include <iostream>
#include <cstdlib>
#include <QMessageBox>
#include <QPointF>
#include <QDebug>
#include <string.h>

using namespace boost;

panel::panel(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    this->setSceneRect(50,50,550,550); //default size of the panel's scene
    this->setScene(scene);

    //signals recieved from tab
    connect(parent, SIGNAL(setmode(int)), this, SLOT(changemode(int)));
    connect(parent, SIGNAL(setcolor(int)), this, SLOT(changecolor(int)));

    //setting default values to variables
    radius = 8;
    mode = 0;
    edging = 0;
    current_num = 1;
}

void panel::mousePressEvent(QMouseEvent *e)
{
    if (mode == 1)           //Add Vertex mode
    {
        if (e->buttons() == Qt::LeftButton)
        {
            QPointF pt = mapToScene(e->pos());
            mypoint* pnt = new mypoint(this);
            QRect r = QRect(pt.x() - 8, pt.y() - 8, 2 * 8, 2 * 8); //we use default values to place a point

            pnt->defpos = pt;
            pnt->currentpos = pt;
            pnt->setRect(r);
            pnt->num = current_num;
            pnt->color = color;
            pnt->tempcol = color;
            pnt->setBrush(color);
            pnt->setTransformOriginPoint(pt);

            QString s = QString::number(current_num);
            pnt->text->setPlainText(s);
            QPointF textpt;

            if (current_num > 9) textpt = QPointF(pnt->currentpos.x() - 8 * 1.3, pnt->currentpos.y() - 8 * 1.5); //shift of number's beginning if it consists of 2 symbols
            else textpt = QPointF(pnt->currentpos.x() - 8, pnt->currentpos.y() - 8 * 1.5);

            QFont ft("Times", 10, QFont::Bold);
            pnt->text->setFont(ft);
            pnt->text->setPos(textpt);

            scene->addItem(pnt);
            add_vertex(g);
            current_num++;
            emit set_rad(radius);      //changing radius of all points after adding a point with default radius is easier
        }
    }

    QGraphicsView::mousePressEvent(e); //sending mousePressEvent to items on the scene

}

void panel::edging_start(mypoint *p)   //if a point sent a signal about edging start
{
    p1 = p;
    edging = true;
    emit pan_edging_start();
}

void panel::edging_finish(mypoint *p)  //if another point sent a signal about edging finish
{
    p2 = p;
    edging = false;
    if (p1 != p2)
    {
        permit = 1;
        emit edge_permit(p1, p2);      //send a signal with pointers on both verticies to all edges to prevent parallel edges
        if (permit)
        {
            myline* lin = new myline(this);
            QPen pen;
            pen.setWidth(2 + trunc(radius/8.0)); //set width of the line corresponding to current vertex radius
            pen.setBrush(color);
            lin->color = color;
            lin->setPen(pen);
            lin->setLine(p1->currentpos.x() , p1->currentpos.y() , p2->currentpos.x() , p2->currentpos.y());
            lin->pt1 = p1;
            lin->pt2 = p2;

            //make an edge text slightly higher than middle of the edge (we allow for the size of the letter)
            QPointF textpt = QPointF((p1->currentpos.x() + p2->currentpos.x()) / 2.0 - 10, (p1->currentpos.y() + p2->currentpos.y()) / 2.0 - 20);
            lin->text->setPlainText(tr("1"));
            lin->text->setFont(QFont("Times", radius));
            lin->text->setPos(textpt);
            lin->text->setTextInteractionFlags(Qt::TextEditable);

            scene->addItem(lin);
            add_edge(p1->num,p2->num,this->g);
        }
    }
    emit pan_edging_finish();
}

void panel::edge_draw(int m)
{
    //this slot is multiplies responds of edges on 2 vertex pointers sent before, these responds are 1 or 0 numbers
    //0 is sent if one of the edges found 2 verticies as his 2 verticies so permit is set to 0
    //1 is sent if opposite
    permit *= m;
}

void panel::clear_pushed() //if Clear button was pushed
{
    g.clear();
    current_num = 0;
    scene->clear();
}

void panel::rmp(mypoint* p)  //if one of the verticies was pushe din mode 2
{
    int num = p->num;
    clear_vertex(num, g);
    remove_vertex(num, g);
    emit num_decrease(num);
    emit removenode(p);
    scene->removeItem(p);
    delete p;
}

void panel::rml(myline *l)   //if one of the edges was pushed in mode 2
{
    remove_edge(l->pt1->num,l->pt2->num,g);

    scene->removeItem(l);
    delete l;
}

void panel::rml_node(myline *l)        //if the edge was adjacnet to a removed vertex
{
    QDebug deb = qDebug();
    for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        deb << "(" << index[source(*ei, g)] << "," << index[target(*ei, g)] << ") ";

    scene->removeItem(l);
    delete l;
}

void panel::changemode(int m)
{
    mode = m;
    emit pan_edging_finish();
    emit setmode(m);
}

void panel::changecolor(int c)
{
    emit setcolor(c);
    if (c == 1) this->color = QColor(Qt::gray);
    if (c == 2) this->color = QColor(Qt::red);
    if (c == 3) this->color = QColor(Qt::yellow);
    if (c == 4) this->color = QColor(Qt::green);
}

void panel::pmv(mypoint *p)       //recieve signal about point move and send a signal to adjacent edges
{
    emit lmv(p);
}

void panel::plane_check()         //if the Planarity button was pushed
{
    QMessageBox* msg = new QMessageBox();
    if (boyer_myrvold_planarity_test(g)) msg->setText(tr("YES"));
    else msg->setText(tr("NO"));
    msg->show();
}

void panel::set_point_rad(int r)  //if the value of Radius spinbox on tab changed
{
    radius = r;
    emit set_rad(r);
}
