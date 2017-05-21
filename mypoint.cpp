#include "mypoint.h"

mypoint::mypoint(QWidget* parent) :
    QWidget(parent), QGraphicsEllipseItem()
{


    this->setPen(QPen(Qt::black));                         //edge of vertex color - black
    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);  //neceassary to move edges when adjacent vertex moves

    mode = 0;
    edging = false;
    buffer = QPointF(0,0);
    //signals recieved from panel
    connect(parent,SIGNAL(setmode(int)),this,SLOT(changemode(int)));
    connect(parent, SIGNAL(setcolor(int)), this, SLOT(changecolor(int)));
    connect(parent, SIGNAL(pan_edging_start()), this, SLOT(pan_edging_started()));
    connect(parent, SIGNAL(pan_edging_finish()), this, SLOT(pan_edging_finished()));
    connect(parent, SIGNAL(set_rad(int)), this, SLOT(set_rad(int)));
    connect(parent, SIGNAL(num_decrease(int)), this, SLOT(num_decrease(int)));
    //signals sent to the panel
    connect(this, SIGNAL(removepoint(mypoint*)),parent,SLOT(rmp(mypoint*)));
    connect(this, SIGNAL(edge_begin(mypoint*)), parent, SLOT(edging_start(mypoint*)));
    connect(this, SIGNAL(edge_end(mypoint*)), parent, SLOT(edging_finish(mypoint*)));
    connect(this, SIGNAL(pointmove(mypoint*)), parent, SLOT(pmv(mypoint*)));

}


void mypoint::mousePressEvent(QGraphicsSceneMouseEvent *c)
{
    if (c->buttons() == Qt::LeftButton)
    {
        if (mode == 2)                                     //Remove Mode
        {
            emit removepoint(this);
        }
        if (mode == 4)                                     //Add Edge Mode
        {
            if (edging == false)
            {

                this->setBrush(Qt::blue);                  //blue is only for vertex being connected to another
                emit edge_begin(this);
            }
            else if (edging == true)
            {
                emit edge_end(this);
            }
        }
        if (mode == 5)                                     //Colorize mode
        {
            this->setBrush(color);
            this->tempcol = color;
        }
    }

}

void mypoint::changemode(int m)
{
    mode = m;

    if (m == 3)
    {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
    }
        else this->setFlag(QGraphicsItem::ItemIsMovable, false);
}

void mypoint::changecolor(int c)
{
    if (c == 1) this->color = QColor(Qt::gray);
    if (c == 2) this->color = QColor(Qt::red);
    if (c == 3) this->color = QColor(Qt::yellow);
    if (c == 4) this->color = QColor(Qt::green);
}

void mypoint::pan_edging_started()               //is activated after clicking on 1 of the verticies in Add Edge mode
{
    edging = true;
}

void mypoint::pan_edging_finished()              //is activated after the edge adding is finished or aborted
{
    edging = false;
    this->setBrush(tempcol);
}

QVariant mypoint::itemChange(GraphicsItemChange change, const QVariant &value)
{
    //this function is activated every time the vertex is moved in mode 3
    if (change == ItemScenePositionHasChanged && scene())
    {
        //the currentpos is updated (recursive way is now recommended so the defpos is involved)
        this->currentpos = QPointF(this->scenePos().x() + defpos.x() - buffer.x(), this->scenePos().y() + defpos.y() - buffer.y());
        emit pointmove(this);          //signal sent to adjacent lines via panel
    }
    return QGraphicsItem::itemChange(change,value);
}

void mypoint::set_rad(int r)           //scaling of vertex
{
    //here the buffer variable is increased by the change of point's scenePos
    //so as to substract this value from currentpos in itemChange
    setTransformOriginPoint(defpos);
    buffer.setX(buffer.x() - this->scenePos().x());
    buffer.setY(buffer.y() - this->scenePos().y());
    this->setScale(r/8.0);
    buffer.setX(buffer.x() + this->scenePos().x());
    buffer.setY(buffer.y() + this->scenePos().y());
}


void mypoint::num_decrease(int n)
{
    //this function is called after vertex with number n was removed
    //to prevent wrong enumertion caused by Vertexlist being vecS
    if (this->num > n) this->num -= 1;
}
