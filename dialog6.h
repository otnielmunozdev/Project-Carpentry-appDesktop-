#ifndef DIALOG6_H
#define DIALOG6_H

#include <QDialog>

namespace Ui {
class Dialog6;
}

class Dialog6 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog6(QWidget *parent = 0);
    ~Dialog6();

private slots:
    void on_MostrarpushButton_clicked();

    void on_BuscarpushButton_clicked();

private:
    Ui::Dialog6 *ui;
};

#endif // DIALOG6_H
