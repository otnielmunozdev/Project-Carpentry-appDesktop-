#include "dialog3.h"
#include "ui_dialog3.h"
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

Dialog3::Dialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3)
{
    ui->setupUi(this);
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("MAC.db");

}

Dialog3::~Dialog3()
{
    delete ui;
}

void Dialog3::habilitar3()
{
    if(ui->NombreEmpleadolineEdit->text().length() > 0 && ui->DomiciliolineEdit->text().length() > 0 && ui->NumeroContactolineEdit->text().length() > 0 && ui->FechaEntradalineEdit->text().length() > 0)
    {
        ui->RegistrarpushButton->setEnabled(true);
    }
    else
    {
        ui->RegistrarpushButton->setEnabled(false);
    }
}

void Dialog3::on_NombreEmpleadolineEdit_textChanged(const QString &arg1)
{
    habilitar3();
}

void Dialog3::on_DomiciliolineEdit_textChanged(const QString &arg1)
{
    habilitar3();
}

void Dialog3::on_NumeroContactolineEdit_textChanged(const QString &arg1)
{
    habilitar3();
}

void Dialog3::on_FechaEntradalineEdit_textChanged(const QString &arg1)
{
    habilitar3();
}

void Dialog3::habilitar3_1()
{
    if(ui->NombreEmpleadoEMlineEdit->text().length() > 0 && ui->DomicilioEMlineEdit->text().length() > 0 && ui->NumeroContactoEMlineEdit->text().length() > 0 && ui->FechaEntradaEMlineEdit->text().length() > 0)
    {
        ui->ModificarEmpleadoDistribuidorpushButton->setEnabled(true);
        ui->EliminarEmpleadopushButton->setEnabled(true);
    }
    else
    {
        ui->ModificarEmpleadoDistribuidorpushButton->setEnabled(false);
        ui->EliminarEmpleadopushButton->setEnabled(false);
    }
}



void Dialog3::on_NombreEmpleadoEMlineEdit_textChanged(const QString &arg1)
{
    habilitar3_1();
}

void Dialog3::on_DomicilioEMlineEdit_textChanged(const QString &arg1)
{
    habilitar3_1();
}

void Dialog3::on_NumeroContactoEMlineEdit_textChanged(const QString &arg1)
{
    habilitar3_1();
}

void Dialog3::on_FechaEntradaEMlineEdit_textChanged(const QString &arg1)
{
    habilitar3_1();
}

void Dialog3::on_RegistrarpushButton_clicked()
{
    MainWindow conn;
    QString  nombre, domicilio, num_contacto, fecha_entrada;
    nombre = ui->NombreEmpleadolineEdit->text();
    domicilio = ui->DomiciliolineEdit->text();
    num_contacto = ui->NumeroContactolineEdit->text();
    fecha_entrada = ui->FechaEntradalineEdit->text();

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into empleados (nombre, domicilio, num_contacto, fecha_entrada) values ('"+nombre+"', '"+domicilio+"','"+num_contacto+"','"+fecha_entrada+"')");

    if(qry.exec())
    {
        QMessageBox::information(this,tr(".......................Save...................!!"),tr("     !!Los datos se guardaron!!     "));
         ui->NombreEmpleadolineEdit->clear();
         ui->DomiciliolineEdit->clear();
         ui->NumeroContactolineEdit->clear();
         ui->FechaEntradalineEdit->clear();

        conn.connClose();
        on_MostrarEmpleadopushButton_clicked();
     }
     else

            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}


void Dialog3::on_MostrarEmpleadopushButton_clicked()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);
    qry->prepare("SELECT * from empleados");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView3->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}

void Dialog3::on_BuscarEmpleadopushButton_clicked()
{
    QString buscar=ui->BuscarEmpleadolineEdit->text();
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from empleados WHERE  id = '"+buscar+"' or nombre = '"+buscar+"' or domicilio = '"+buscar+"' or num_contacto = '"+ buscar+"'or fecha_entrada = '"+ buscar+"'");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView3->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}



void Dialog3::on_tableView3_activated(const QModelIndex &index)
{
    QString val = ui->tableView3->model()->data(index).toString();

    MainWindow conn;
    QString  id, nombre, domicilio, num_contacto, fecha_entrada;
    id = ui->IDEmpleadoslineEdit->text();
    nombre = ui->NombreEmpleadoEMlineEdit->text();
    domicilio = ui->DomicilioEMlineEdit->text();
    num_contacto = ui->NumeroContactoEMlineEdit->text();
    fecha_entrada = ui->FechaEntradaEMlineEdit->text();
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from empleados WHERE id='"+val+"' or nombre = '"+val+"' or domicilio = '"+val+"' or num_contacto = '"+val+"'");

    if(qry.exec())
    {
         QMessageBox::information(this,tr("                    [Activado]                    "),tr("     Los datos se han activado se pueden modificar o eliminar     "));
        while(qry.next())
        {
            ui->IDEmpleadoslineEdit->setText(qry.value(0).toString());
            ui->NombreEmpleadoEMlineEdit->setText(qry.value(1).toString());
            ui->DomicilioEMlineEdit->setText(qry.value(2).toString());
            ui->NumeroContactoEMlineEdit->setText(qry.value(3).toString());
            ui->FechaEntradaEMlineEdit->setText(qry.value(4).toString());
            ui->ModificarEmpleadoDistribuidorpushButton->setEnabled(true);
            ui->EliminarEmpleadopushButton->setEnabled(true);
            ui->NombreEmpleadoEMlineEdit->setEnabled(true);
            ui->DomicilioEMlineEdit->setEnabled(true);
            ui->NumeroContactoEMlineEdit->setEnabled(true);
            ui->FechaEntradaEMlineEdit->setEnabled(true);
        }
        conn.connClose();
     }
     else

            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void Dialog3::on_ModificarEmpleadoDistribuidorpushButton_clicked()
{
    MainWindow conn;
    QString  id, nombre, domicilio, num_contacto, fecha_entrada;
    id = ui->IDEmpleadoslineEdit->text();
    nombre = ui->NombreEmpleadoEMlineEdit->text();
    domicilio = ui->DomicilioEMlineEdit->text();
    num_contacto = ui->NumeroContactoEMlineEdit->text();
    fecha_entrada = ui->FechaEntradaEMlineEdit->text();
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update empleados set nombre = '"+nombre+"', domicilio = '"+domicilio+"', num_contacto = '"+num_contacto+"', fecha_entrada = '"+fecha_entrada+"' where id ='"+id+"'");

    if(qry.exec())
    {
        QMessageBox::information(this,tr("                       [Empleados]               "),tr("          El Empleado se ha modificado correctamente     "));
        ui->IDEmpleadoslineEdit->clear();
        ui->NombreEmpleadoEMlineEdit->clear();
        ui->DomicilioEMlineEdit->clear();
        ui->NumeroContactoEMlineEdit->clear();
        ui->FechaEntradaEMlineEdit->clear();
        ui->EliminarEmpleadopushButton->setEnabled(false);
        ui->ModificarEmpleadoDistribuidorpushButton->setEnabled(false);
        ui->NombreEmpleadoEMlineEdit->setEnabled(false);
        ui->DomicilioEMlineEdit->setEnabled(false);
        ui->NumeroContactoEMlineEdit->setEnabled(false);
        ui->FechaEntradaEMlineEdit->setEnabled(false);
        conn.connClose();
        on_MostrarEmpleadopushButton_clicked();
     }
     else
         QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void Dialog3::on_EliminarEmpleadopushButton_clicked()
{
    MainWindow conn;
    QString  id, nombre, domicilio, num_contacto, fecha_entrada;
    id = ui->IDEmpleadoslineEdit->text();
    nombre = ui->NombreEmpleadoEMlineEdit->text();
    domicilio = ui->DomicilioEMlineEdit->text();
    num_contacto = ui->NumeroContactoEMlineEdit->text();
    fecha_entrada = ui->FechaEntradaEMlineEdit->text();
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("Delete from empleados where id = '"+id+"'" );

    if(qry.exec())
    {
        QMessageBox::information(this,tr("                       [Empleados]               "),tr("          El Empleado se ha eliminado correctamente     "));
        ui->IDEmpleadoslineEdit->clear();
        ui->NombreEmpleadoEMlineEdit->clear();
        ui->DomicilioEMlineEdit->clear();
        ui->NumeroContactoEMlineEdit->clear();
        ui->FechaEntradaEMlineEdit->clear();
        ui->EliminarEmpleadopushButton->setEnabled(false);
        ui->ModificarEmpleadoDistribuidorpushButton->setEnabled(false);
        ui->NombreEmpleadoEMlineEdit->setEnabled(false);
        ui->DomicilioEMlineEdit->setEnabled(false);
        ui->NumeroContactoEMlineEdit->setEnabled(false);
        ui->FechaEntradaEMlineEdit->setEnabled(false);
        conn.connClose();
        on_MostrarEmpleadopushButton_clicked();
     }
     else
         QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}
