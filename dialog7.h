#ifndef DIALOG7_H
#define DIALOG7_H

#include <QDialog>

namespace Ui {
class Dialog7;
}

class Dialog7 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog7(QWidget *parent = 0);
    ~Dialog7();

private slots:
    void on_MostrarpushButton_clicked();

    void on_BuscarpushButton_clicked();

    void on_MostrarpushButton_2_clicked();

    void on_BuscarpushButton_2_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_EntregarpushButton_clicked();

private:
    Ui::Dialog7 *ui;
};

#endif // DIALOG7_H
