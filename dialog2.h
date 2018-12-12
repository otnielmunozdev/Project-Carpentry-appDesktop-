#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>

namespace Ui {
class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2(QWidget *parent = 0);
    ~Dialog2();
    void Habilitar2();
    void Habilitar2_1();

private slots:

    void on_NombreProovedoreslineEdit_textChanged(const QString &arg1);

    void on_NumeroProovedoreslineEdit_textChanged(const QString &arg1);

    void on_TipoServicioProovedoreslineEdit_textChanged(const QString &arg1);

    void on_RegistrarProovedorpushButton_clicked();

    void on_MostrarProovedorpushButton_clicked();

    void on_BuscarProovedorpushButton_clicked();

    void on_tableView2_activated(const QModelIndex &index);

    void on_ModificarProovedorespushButton_clicked();

    void on_EliminarProovedorespushButton_clicked();

    void on_NombreProovedoresEMlineEdit_textChanged(const QString &arg1);

    void on_NumeroProovedoresEMlineEdit_textChanged(const QString &arg1);

    void on_TipoServicioProovedoresEMlineEdit_textChanged(const QString &arg1);

private:
    Ui::Dialog2 *ui;
};

#endif // DIALOG2_H
