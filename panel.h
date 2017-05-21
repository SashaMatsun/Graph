#ifndef PANEL_H
#define PANEL_H

#include <cstdlib>
#include <iterator>
#include "boost/graph/graph_utility.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/boyer_myrvold_planar_test.hpp"

#include "myline.h"
#include "mypoint.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QDebug>
#include <QFont>


//using namespace boost;


class panel : public QGraphicsView
{
    Q_OBJECT

public:
    explicit panel(QWidget *parent = 0);
    int mode;                //current mode
    int edging;              //variable that is true if one vertex is pressed in 4 mode
    int current_num;         //number that new added vertex will have
    int permit;              //variable used to understand if we can add an edge between 2 verticies
    double radius;           //current radius of verticies
    QColor color;            //current color chosen on tab (NOT brush of anything)

    //use boost templates to create our own graph type
    typedef boost::adjacency_list<
            boost::vecS, boost::vecS, boost::undirectedS> graph_t;
    graph_t g;

    //the same for index map (it is needed for adding and removing edges)
    typedef boost::property_map<graph_t, boost::vertex_index_t>::type IndexMap;
    IndexMap index;
    boost::graph_traits<graph_t>::edge_iterator ei, ei_end;


public slots:
    void mousePressEvent(QMouseEvent* e);

    void clear_pushed();
    void plane_check();

    void rmp(mypoint* p);
    void rml(myline* l);
    void rml_node(myline *l);
    void pmv(mypoint* p);

    void changemode(int m);
    void changecolor(int c);

    void edging_start(mypoint* p);
    void edging_finish(mypoint* p);
    void edge_draw(int m);

    void set_point_rad(int r);


signals:
    void setmode(int m);
    void setcolor(int c);
    void pan_edging_start();
    void pan_edging_finish();
    void removenode(mypoint* p);
    void lmv(mypoint* p);
    void edge_permit(mypoint* p1, mypoint* p2);
    void set_rad(int r);
    void num_decrease(int n);

private:
    mypoint* p1;
    mypoint* p2;
    QGraphicsScene* scene;
};

#endif // PANEL_H
