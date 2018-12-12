#ifndef DIALOG5_H
#define DIALOG5_H

#include <QDialog>

namespace Ui {
class Dialog5;
}

class Dialog5 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog5(QWidget *parent = 0);
    ~Dialog5();
    void habilitar5();
    void habilitar5_1();

private slots:
    void on_RegistrarClientepushButton_clicked();

    void on_NombreClientelineEdit_textChanged(const QString &arg1);

    void on_DomicilioClientelineEdit_textChanged(const QString &arg1);

    void on_NumeroContactoClientelineEdit_textChanged(const QString &arg1);

    void on_NombreClienteEMlineEdit_textChanged(const QString &arg1);

    void on_DomicilioClienteEMlineEdit_textChanged(const QString &arg1);

    void on_NumeroClienteEMlineEdit_textChanged(const QString &arg1);

    void on_MostrarClientepushButton_clicked();

    void on_BuscarClientepushButton_clicked();

    void on_tableView3_2_activated(const QModelIndex &index);

    void on_ModificarEmpleadoClientepushButton_clicked();

    void on_EliminarClientepushButton_clicked();

private:
    Ui::Dialog5 *ui;
};

#endif // DIALOG5_H
