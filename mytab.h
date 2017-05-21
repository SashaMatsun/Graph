#ifndef MYTAB_H
#define MYTAB_H

#include "panel.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>

namespace Ui {
class mytab;
}

class mytab : public QWidget
{
    Q_OBJECT

public:
    explicit mytab(QWidget *parent = 0);
    ~mytab();

private slots:
    void setaddmode();
    void setremovemode();
    void setmovemode();
    void setedgeaddmode();

    void setgraycolor();
    void setredcolor();
    void setyellowcolor();
    void setgreencolor();
    void setcolormode();

signals:
    void setmode(int m);
    void setcolor(int c);

private:
    Ui::mytab *ui;
};

#endif // MYTAB_H
