#ifndef DIALOG3_H
#define DIALOG3_H

#include <QDialog>

namespace Ui {
class Dialog3;
}

class Dialog3 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3(QWidget *parent = 0);
    ~Dialog3();
    void habilitar3();
    void habilitar3_1();

private slots:
    void on_RegistrarpushButton_clicked();

    void on_NombreEmpleadolineEdit_textChanged(const QString &arg1);

    void on_DomiciliolineEdit_textChanged(const QString &arg1);

    void on_NumeroContactolineEdit_textChanged(const QString &arg1);

    void on_FechaEntradalineEdit_textChanged(const QString &arg1);

    void on_NombreEmpleadoEMlineEdit_textChanged(const QString &arg1);

    void on_DomicilioEMlineEdit_textChanged(const QString &arg1);

    void on_NumeroContactoEMlineEdit_textChanged(const QString &arg1);

    void on_FechaEntradaEMlineEdit_textChanged(const QString &arg1);

    void on_MostrarEmpleadopushButton_clicked();

    void on_BuscarEmpleadopushButton_clicked();

    void on_tableView3_activated(const QModelIndex &index);

    void on_ModificarEmpleadoDistribuidorpushButton_clicked();

    void on_EliminarEmpleadopushButton_clicked();

private:
    Ui::Dialog3 *ui;
};

#endif // DIALOG3_H
