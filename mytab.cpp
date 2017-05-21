#include "mytab.h"
#include "ui_mytab.h"

mytab::mytab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mytab)
{
    ui->setupUi(this);

    ui->radius->setValue(8);               // 8 is default radius
    ui->radius->setMinimum(8);


    // Sending signals to panel
    connect(ui->radius, SIGNAL(valueChanged(int)), ui->p, SLOT(set_point_rad(int)));
    connect(ui->plan, SIGNAL(pressed()), ui->p, SLOT(plane_check()));
    connect(ui->clear, SIGNAL(pressed()), ui->p, SLOT(clear_pushed()));

    //Recieving signals from buttons
    connect(ui->add, SIGNAL(clicked(bool)), this, SLOT(setaddmode()));
    connect(ui->rm, SIGNAL(clicked(bool)), this, SLOT(setremovemode()));
    connect(ui->mv, SIGNAL(clicked(bool)), this, SLOT(setmovemode()));
    connect(ui->edge, SIGNAL(clicked(bool)), this, SLOT(setedgeaddmode()));
    connect(ui->color, SIGNAL(clicked(bool)), this, SLOT(setcolormode()));

    connect(ui->gray, SIGNAL(clicked(bool)), this, SLOT(setgraycolor()));
    connect(ui->red, SIGNAL(clicked(bool)), this, SLOT(setredcolor()));
    connect(ui->yellow, SIGNAL(clicked(bool)), this, SLOT(setyellowcolor()));
    connect(ui->green, SIGNAL(clicked(bool)), this, SLOT(setgreencolor()));

    ui->gray->click();                      // gray is default color
}

mytab::~mytab()
{
    delete ui;
}

// Mode and color setting functions
// modes: 1 - Add Vertex, 2 - Remove (anything), 3 - Move vertex, 4 - Add edge between 2 verticies
// colors: 1 - Gray, 2 - Red, 3 - Yellow, 4 - Purple

void mytab::setaddmode()
{
    emit setmode(1);
}

void mytab::setremovemode()
{
    emit setmode(2);
}

void mytab::setmovemode()
{
    emit setmode(3);
}

void mytab::setedgeaddmode()
{
    emit setmode(4);
}

void mytab::setcolormode()
{
    emit setmode(5);
}

void mytab::setgraycolor()
{
    emit setcolor(1);
}

void mytab::setredcolor()
{
    emit setcolor(2);
}

void mytab::setyellowcolor()
{
    emit setcolor(3);
}

void mytab::setgreencolor()
{
    emit setcolor(4);
}
