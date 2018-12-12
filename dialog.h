#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void Habilitar();
    void Habilitar_2();

private slots:
    void on_RegistrarpushButton_clicked();

    void on_MostrarpushButton_clicked();

    void on_FechaPedidolineEdit_textChanged(const QString &arg1);

    void on_FechaEntregalineEdit_textChanged(const QString &arg1);

    void on_EspecificacionestextEdit_textChanged();

    void on_DetallestextEdit_textChanged();

    void on_ClientepushButton_clicked();

    void on_NombrePedidolineEdit_textChanged(const QString &arg1);

    void on_CostolineEdit_textChanged(const QString &arg1);

    void on_PrioridadlineEdit_textChanged(const QString &arg1);

    void on_IDCLientelineEdit_textChanged(const QString &arg1);

    void on_BuscarpushButton_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_MostrarAltapushButton_clicked();

    void on_BuscarAltapushButton_clicked();

    void on_MostrarMediapushButton_clicked();

    void on_BuscarMediapushButton_clicked();

    void on_MostrarBajapushButton_clicked();

    void on_BuscarBajapushButton_clicked();

    void on_ModificarpushButton_clicked();

    void on_tableView_2_activated(const QModelIndex &index);

    void on_tableView_3_activated(const QModelIndex &index);

    void on_tableView_4_activated(const QModelIndex &index);

    void on_EliminarpushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
