#include "dialog2.h"
#include "ui_dialog2.h"
#include <mainwindow.h>
#include "mainwindow.h"
#include <mainwindow1.h>
#include "mainwindow1.h"
#include <QtSql>
#include <QFileInfo>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QtWidgets>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <stdio.h>
#include <QToolBar>

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("MAC.db");

}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::Habilitar2()
{
    if(ui->NombreProovedoreslineEdit->text().length() > 0 && ui->NumeroProovedoreslineEdit->text().length() > 0 && ui->TipoServicioProovedoreslineEdit->text().length() > 0 )
    {
        ui->RegistrarProovedorpushButton->setEnabled(true);
    }
    else
    {
        ui->RegistrarProovedorpushButton->setEnabled(false);
    }
}

void Dialog2::Habilitar2_1()
{
    if(ui->NombreProovedoresEMlineEdit->text().length() > 0 && ui->NumeroProovedoresEMlineEdit->text().length() > 0 && ui->TipoServicioProovedoresEMlineEdit->text().length() > 0 )
    {
        ui->ModificarProovedorespushButton->setEnabled(true);
        ui->EliminarProovedorespushButton->setEnabled(true);
    }
    else
    {
        ui->ModificarProovedorespushButton->setEnabled(false);
        ui->EliminarProovedorespushButton->setEnabled(false);
    }
}

void Dialog2::on_NombreProovedoresEMlineEdit_textChanged(const QString &arg1)
{
    Habilitar2_1();
}

void Dialog2::on_NumeroProovedoresEMlineEdit_textChanged(const QString &arg1)
{
    Habilitar2_1();
}

void Dialog2::on_TipoServicioProovedoresEMlineEdit_textChanged(const QString &arg1)
{
    Habilitar2();
}


void Dialog2::on_NombreProovedoreslineEdit_textChanged(const QString &arg1)
{
    Habilitar2();
}

void Dialog2::on_NumeroProovedoreslineEdit_textChanged(const QString &arg1)
{
    Habilitar2();
}

void Dialog2::on_TipoServicioProovedoreslineEdit_textChanged(const QString &arg1)
{
    Habilitar2();
}


void Dialog2::on_RegistrarProovedorpushButton_clicked()
{
        MainWindow conn;
        QString  nombre, num_proovedor, tipo_proovedor;
        nombre = ui->NombreProovedoreslineEdit->text();
        num_proovedor = ui->NumeroProovedoreslineEdit->text();
        tipo_proovedor = ui->TipoServicioProovedoreslineEdit->text();

        conn.connOpen();
        QSqlQuery qry;
        qry.prepare("insert into proovedores (nombre, num_proovedor, tipo_proovedor) values ('"+nombre+"', '"+num_proovedor+"','"+tipo_proovedor+"')");

        if(qry.exec())
        {
            QMessageBox::information(this,tr(".......................Save...................!!"),tr("     !!Los datos se guardaron!!     "));
             ui->NombreProovedoreslineEdit->clear();
             ui->NumeroProovedoreslineEdit->clear();
             ui->TipoServicioProovedoreslineEdit->clear();

            conn.connClose();
            on_MostrarProovedorpushButton_clicked();
         }
         else

                QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}
void Dialog2::on_MostrarProovedorpushButton_clicked()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);
    qry->prepare("SELECT * from proovedores");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView2->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}


void Dialog2::on_BuscarProovedorpushButton_clicked()
{
    QString buscar=ui->BuscarProovedoreslineEdit->text();
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from proovedores WHERE  id = '"+buscar+"' or nombre = '"+buscar+"' or num_proovedor = '"+buscar+"' or tipo_proovedor = '"+ buscar+"'");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView2->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}


void Dialog2::on_tableView2_activated(const QModelIndex &index)
{
    QString val = ui->tableView2->model()->data(index).toString();

    MainWindow conn;
    QString  id, nombre, num_proovedor, tipo_proovedor;
    id = ui->IDProovedoreslineEdit->text();
    nombre = ui->NombreProovedoresEMlineEdit->text();
    num_proovedor = ui->NumeroProovedoresEMlineEdit->text();
    tipo_proovedor = ui->TipoServicioProovedoresEMlineEdit->text();

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from proovedores WHERE id='"+val+"' or nombre = '"+val+"' or num_proovedor = '"+val+"' or tipo_proovedor = '"+val+"'");

    if(qry.exec())
    {
         QMessageBox::information(this,tr("                    Activado                    "),tr("     Los datos se han activado se pueden modificar o eliminar     "));
        while(qry.next())
        {
            ui->IDProovedoreslineEdit->setText(qry.value(0).toString());
            ui->NombreProovedoresEMlineEdit->setText(qry.value(1).toString());
            ui->NumeroProovedoresEMlineEdit->setText(qry.value(2).toString());
            ui->TipoServicioProovedoresEMlineEdit->setText(qry.value(3).toString());
            ui->ModificarProovedorespushButton->setEnabled(true);
            ui->EliminarProovedorespushButton->setEnabled(true);
            ui->NombreProovedoresEMlineEdit->setEnabled(true);
            ui->NumeroProovedoresEMlineEdit->setEnabled(true);
            ui->TipoServicioProovedoresEMlineEdit->setEnabled(true);
        }
        conn.connClose();
     }
     else

            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void Dialog2::on_ModificarProovedorespushButton_clicked()
{
    MainWindow conn;
    QString  id, nombre, num_proovedor, tipo_proovedor;
    id = ui->IDProovedoreslineEdit->text();
    nombre = ui->NombreProovedoresEMlineEdit->text();
    num_proovedor = ui->NumeroProovedoresEMlineEdit->text();
    tipo_proovedor = ui->TipoServicioProovedoresEMlineEdit->text();
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update proovedores set nombre = '"+nombre+"', num_proovedor = '"+num_proovedor+"', tipo_proovedor = '"+tipo_proovedor+"' where id ='"+id+"'" );

    if(qry.exec())
    {
        QMessageBox::information(this,tr("                       Proovedores               "),tr("          El Proovedor se ha modificado correctamente     "));
        ui->IDProovedoreslineEdit->clear();
        ui->NombreProovedoresEMlineEdit->clear();
        ui->NumeroProovedoresEMlineEdit->clear();
        ui->TipoServicioProovedoresEMlineEdit->clear();
        ui->EliminarProovedorespushButton->setEnabled(false);
        ui->ModificarProovedorespushButton->setEnabled(false);
        ui->NombreProovedoresEMlineEdit->setEnabled(false);
        ui->NumeroProovedoresEMlineEdit->setEnabled(false);
        ui->TipoServicioProovedoresEMlineEdit->setEnabled(false);
        conn.connClose();
        on_MostrarProovedorpushButton_clicked();
     }
     else
         QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void Dialog2::on_EliminarProovedorespushButton_clicked()
{
    MainWindow conn;
    QString  id, nombre, num_proovedor, tipo_proovedor;
    id = ui->IDProovedoreslineEdit->text();
    nombre = ui->NombreProovedoresEMlineEdit->text();
    num_proovedor = ui->NumeroProovedoresEMlineEdit->text();
    tipo_proovedor = ui->TipoServicioProovedoresEMlineEdit->text();
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("Delete from proovedores where id = '"+id+"'" );

    if(qry.exec())
    {
        QMessageBox::information(this,tr("                       Proovedores               "),tr("          El Proovedor se ha eliminado correctamente     "));
        ui->IDProovedoreslineEdit->clear();
        ui->NombreProovedoresEMlineEdit->clear();
        ui->NumeroProovedoresEMlineEdit->clear();
        ui->TipoServicioProovedoresEMlineEdit->clear();
        ui->EliminarProovedorespushButton->setEnabled(false);
        ui->ModificarProovedorespushButton->setEnabled(false);
        ui->NombreProovedoresEMlineEdit->setEnabled(false);
        ui->NumeroProovedoresEMlineEdit->setEnabled(false);
        ui->TipoServicioProovedoresEMlineEdit->setEnabled(false);
        conn.connClose();
        on_MostrarProovedorpushButton_clicked();
     }
     else
         QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

