#ifndef DIALOG4_H
#define DIALOG4_H

#include <QDialog>

namespace Ui {
class Dialog4;
}

class Dialog4 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog4(QWidget *parent = 0);
    ~Dialog4();
    void Habilitar4();
    void Habilitar4_1();

private slots:
    void on_RegistrarpushButton_clicked();

    void on_NombreDistribuidorlineEdit_textChanged(const QString &arg1);

    void on_NumeroDistribuidorlineEdit_textChanged(const QString &arg1);

    void on_TipoServiciodistribuidorlineEdit_textChanged(const QString &arg1);

    void on_MostrarDistribuidorpushButton_clicked();

    void on_BuscarpushButton_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_ModificarDistribuidorpushButton_clicked();

    void on_EliminarDistribuidorpushButton_clicked();

    void on_NombreDistribuidorEMlineEdit_textChanged(const QString &arg1);

    void on_NumeroDistribuidorEMlineEdit_textChanged(const QString &arg1);

    void on_TipoServiciodistribuidorEMlineEdit_textChanged(const QString &arg1);

private:
    Ui::Dialog4 *ui;
};

#endif // DIALOG4_H
