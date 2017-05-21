#ifndef NAMEWIN_H
#define NAMEWIN_H

#include <QDialog>

namespace Ui {
class namewin;
}

class namewin : public QDialog
{
    Q_OBJECT

public:
    explicit namewin(QWidget *parent = 0);
    ~namewin();

private slots:
    void on_nameline_textChanged(const QString &arg1);

    void on_done_clicked();

signals:
    void gdone(QString name);

private:
    Ui::namewin *ui;
};

#endif // NAMEWIN_H
