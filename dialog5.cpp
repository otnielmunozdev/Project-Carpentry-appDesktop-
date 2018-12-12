#include "dialog5.h"
#include "ui_dialog5.h"
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

Dialog5::Dialog5(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog5)
{
    ui->setupUi(this);
    on_MostrarClientepushButton_clicked();
}

Dialog5::~Dialog5()
{
    delete ui;
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("MAC.db");
}

void Dialog5::habilitar5()
{
    if(ui->NombreClientelineEdit->text().length() > 0 && ui->DomicilioClientelineEdit->text().length() > 0 && ui->NumeroContactoClientelineEdit->text().length() > 0 )
    {
        ui->RegistrarClientepushButton->setEnabled(true);
    }
    else
    {
        ui->RegistrarClientepushButton->setEnabled(false);
    }
}


void Dialog5::habilitar5_1()
{
    if(ui->NombreClienteEMlineEdit->text().length() > 0 && ui->DomicilioClienteEMlineEdit->text().length() > 0 && ui->NumeroClienteEMlineEdit->text().length() > 0 )
    {
        ui->ModificarEmpleadoClientepushButton->setEnabled(true);
        ui->EliminarClientepushButton->setEnabled(true);
    }
    else
    {
        ui->ModificarEmpleadoClientepushButton->setEnabled(false);
        ui->EliminarClientepushButton->setEnabled(false);
    }
}



void Dialog5::on_NombreClientelineEdit_textChanged(const QString &arg1)
{
    habilitar5();
}

void Dialog5::on_DomicilioClientelineEdit_textChanged(const QString &arg1)
{
    habilitar5();
}

void Dialog5::on_NumeroContactoClientelineEdit_textChanged(const QString &arg1)
{
    habilitar5();
}


void Dialog5::on_NombreClienteEMlineEdit_textChanged(const QString &arg1)
{
    habilitar5_1();
}

void Dialog5::on_DomicilioClienteEMlineEdit_textChanged(const QString &arg1)
{
    habilitar5_1();
}

void Dialog5::on_NumeroClienteEMlineEdit_textChanged(const QString &arg1)
{
    habilitar5_1();
}

void Dialog5::on_RegistrarClientepushButton_clicked()
{
    MainWindow conn;
    QString  nombre, domicilio, num_contacto_cliente;
    nombre = ui->NombreClientelineEdit->text();
    domicilio = ui->DomicilioClientelineEdit->text();
    num_contacto_cliente = ui->NumeroContactoClientelineEdit->text();

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into clientes (nombre, domicilio, num_contacto_cliente) values ('"+nombre+"', '"+domicilio+"','"+num_contacto_cliente+"')");

    if(qry.exec())
    {
        QMessageBox::information(this,tr(".......................Save...................!!"),tr("     !!Los datos se guardaron!!     "));
         ui->NombreClientelineEdit->clear();
         ui->DomicilioClientelineEdit->clear();
         ui->NumeroContactoClientelineEdit->clear();

        conn.connClose();
        on_MostrarClientepushButton_clicked();
     }
     else

            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void Dialog5::on_MostrarClientepushButton_clicked()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);
    qry->prepare("SELECT * from clientes");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView3_2->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}

void Dialog5::on_BuscarClientepushButton_clicked()
{
    QString buscar=ui->BuscarClientelineEdit->text();
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from clientes WHERE  id = '"+buscar+"' or nombre = '"+buscar+"' or domicilio = '"+buscar+"' or num_contacto_cliente = '"+ buscar+"'");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView3_2->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}

void Dialog5::on_tableView3_2_activated(const QModelIndex &index)
{
    QString val = ui->tableView3_2->model()->data(index).toString();

    MainWindow conn;
    QString  id, nombre, domicilio, num_contacto_cliente;
    id = ui->IDClientelineEdit->text();
    nombre = ui->NombreClienteEMlineEdit->text();
    domicilio = ui->DomicilioClienteEMlineEdit->text();
    num_contacto_cliente = ui->NumeroClienteEMlineEdit->text();
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from clientes WHERE id='"+val+"' or nombre = '"+val+"'");

    if(qry.exec())
    {
         //QMessageBox::information(this,tr("                    [Activado]                    "),tr("     Los datos se han activado se pueden modificar o eliminar     "));
        while(qry.next())
        {
            ui->IDClientelineEdit->setText(qry.value(0).toString());
            ui->NombreClienteEMlineEdit->setText(qry.value(1).toString());
            ui->DomicilioClienteEMlineEdit->setText(qry.value(2).toString());
            ui->NumeroClienteEMlineEdit->setText(qry.value(3).toString());
            ui->ModificarEmpleadoClientepushButton->setEnabled(true);
            ui->EliminarClientepushButton->setEnabled(true);
            ui->NombreClienteEMlineEdit->setEnabled(true);
            ui->DomicilioClienteEMlineEdit->setEnabled(true);
            ui->NumeroClienteEMlineEdit->setEnabled(true);
        }
        conn.connClose();
     }
     else

            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void Dialog5::on_ModificarEmpleadoClientepushButton_clicked()
{
    MainWindow conn;
    QString  id, nombre, domicilio, num_contacto_cliente;
    id = ui->IDClientelineEdit->text();
    nombre = ui->NombreClienteEMlineEdit->text();
    domicilio = ui->DomicilioClienteEMlineEdit->text();
    num_contacto_cliente = ui->NumeroClienteEMlineEdit->text();
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update clientes set nombre = '"+nombre+"', domicilio = '"+domicilio+"', num_contacto_cliente = '"+num_contacto_cliente+"' where id ='"+id+"'" );

    if(qry.exec())
    {
        QMessageBox::information(this,tr("                       [Clientes]               "),tr("          El Cliente se ha modificado correctamente     "));
        ui->IDClientelineEdit->clear();
        ui->NombreClienteEMlineEdit->clear();
        ui->DomicilioClienteEMlineEdit->clear();
        ui->NumeroClienteEMlineEdit->clear();
        ui->ModificarEmpleadoClientepushButton->setEnabled(false);
        ui->EliminarClientepushButton->setEnabled(false);
        ui->NombreClienteEMlineEdit->setEnabled(false);
        ui->DomicilioClienteEMlineEdit->setEnabled(false);
        ui->NumeroClienteEMlineEdit->setEnabled(false);
        conn.connClose();
        on_MostrarClientepushButton_clicked();
     }
     else
         QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void Dialog5::on_EliminarClientepushButton_clicked()
{
    MainWindow conn;
    QString  id, nombre, domicilio, num_contacto_cliente;
    id = ui->IDClientelineEdit->text();
    nombre = ui->NombreClienteEMlineEdit->text();
    domicilio = ui->DomicilioClienteEMlineEdit->text();
    num_contacto_cliente = ui->NumeroClienteEMlineEdit->text();
    conn.connOpen();
    QSqlQuery qry, qry2;
    qry.prepare("Delete from clientes where id = '"+id+"'" );
    qry2.prepare("Delete from pedido where id_cliente = '"+id+"'");

    if(qry.exec()&& qry2.exec())
    {
        QMessageBox::information(this,tr("                       [Clientes]               "),tr("          El Cliente se ha eliminado correctamente     "));
        ui->IDClientelineEdit->clear();
        ui->NombreClienteEMlineEdit->clear();
        ui->DomicilioClienteEMlineEdit->clear();
        ui->NumeroClienteEMlineEdit->clear();
        ui->ModificarEmpleadoClientepushButton->setEnabled(false);
        ui->EliminarClientepushButton->setEnabled(false);
        ui->NombreClienteEMlineEdit->setEnabled(false);
        ui->DomicilioClienteEMlineEdit->setEnabled(false);
        ui->NumeroClienteEMlineEdit->setEnabled(false);
        conn.connClose();
        on_MostrarClientepushButton_clicked();
     }
     else
         QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}
