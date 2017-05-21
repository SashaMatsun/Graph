#include "namewin.h"
#include "ui_namewin.h"

namewin::namewin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::namewin)
{
    ui->setupUi(this);
    ui->done->setEnabled(false);
}

void namewin::on_nameline_textChanged(const QString &arg1)
{
    if (arg1 == "") ui->done->setEnabled(false);
    else ui->done->setEnabled(true);
}

void namewin::on_done_clicked()
{
    emit gdone(ui->nameline->text());
    this->close();
}

namewin::~namewin()
{
    delete ui;
}
