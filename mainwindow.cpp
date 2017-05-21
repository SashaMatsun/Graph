#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytab.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu *graph = menuBar()->addMenu("Graph");
    QAction *newone = new QAction(tr("Create"), this);
    connect(newone,SIGNAL(triggered()), this, SLOT(gr_cr()));

    graph->addAction(newone);
}

void MainWindow::gr_cr()
{
    namewin *msg = new namewin(this);
    msg->show();
    connect(msg, SIGNAL(gdone(QString)), this, SLOT(addTab(QString)));

}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::addTab(QString name)
{
    int num = ui->tabWidget->addTab(new mytab, name);
    ui->tabWidget->setCurrentIndex(num);
}

MainWindow::~MainWindow()
{
    delete ui;
}

