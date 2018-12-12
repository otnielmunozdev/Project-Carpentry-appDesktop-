#include "dialog7.h"
#include "ui_dialog7.h"
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

Dialog7::Dialog7(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog7)
{
    ui->setupUi(this);
    on_MostrarpushButton_clicked();
    on_MostrarpushButton_2_clicked();
}

Dialog7::~Dialog7()
{
    delete ui;
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("MAC.db");
}

void Dialog7::on_MostrarpushButton_clicked()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);
    qry->prepare("SELECT * from pedido");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}

void Dialog7::on_BuscarpushButton_clicked()
{
    QString buscar=ui->BuscarlineEdit->text();
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from pedido WHERE  nombre_pedido = '"+buscar+"' or fecha_pedido = '"+buscar+"' or fecha_entrega = '"+ buscar+"' or especificaciones = '"+ buscar+"' or detalles = '"+ buscar+"' or costo = '"+ buscar+"' or prioridad = '"+ buscar+"'  or id_cliente = '"+ buscar+"'");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}

void Dialog7::on_MostrarpushButton_2_clicked()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from clientes");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_2->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}

void Dialog7::on_BuscarpushButton_2_clicked()
{
    QString buscar=ui->BuscarlineEdit_2->text();
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from clientes WHERE  id = '"+buscar+"' or nombre = '"+buscar+"' or domicilio = '"+buscar+"' or num_contacto_cliente = '"+ buscar+"'");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_2->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}

void Dialog7::on_tableView_activated(const QModelIndex &index)
{
    MainWindow conn;
    QString val = ui->tableView->model()->data(index).toString();

    QString id, nombre_pedido, fecha_pedido, fecha_entrega, especificaciones, detalles, costo, prioridad, id_cliente; //GUARDARE LA INFORMACION QUE INSERTE EN LOS LINE EDIT
    id = ui->IDPedidolineEdit->text();
    nombre_pedido = ui->NombrePedidolineEdit_2->text();
    fecha_pedido = ui->FechaPedidolineEdit_2->text();
    fecha_entrega = ui->FechaEntregalineEdit_2->text();
    especificaciones = ui->EspecificacionestextEdit_2->toPlainText();
    detalles = ui->DetallestextEdit_2->toPlainText();
    costo = ui->CostolineEdit_2->text();
    prioridad = ui->PrioridadlineEdit_2->text();
    id_cliente = ui->IDCLientelineEdit_2->text();

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from pedido WHERE id='"+val+"' or nombre_pedido = '"+val+"'");

    if(qry.exec())
    {
        // QMessageBox::information(this,tr("                    Activado                    "),tr("     Los datos se han activado se pueden modificar o eliminar     "));
        while(qry.next())
        {
            ui->IDPedidolineEdit->setText(qry.value(0).toString());
            ui->NombrePedidolineEdit_2->setText(qry.value(1).toString());
            ui->FechaPedidolineEdit_2->setText(qry.value(2).toString());
            ui->FechaEntregalineEdit_2->setText(qry.value(3).toString());
            ui->EspecificacionestextEdit_2->setText(qry.value(4).toString());
            ui->DetallestextEdit_2->setText(qry.value(5).toString());
            ui->CostolineEdit_2->setText(qry.value(6).toString());
            ui->PrioridadlineEdit_2->setText(qry.value(7).toString());
            ui->IDCLientelineEdit_2->setText(qry.value(8).toString());
            ui->EntregarpushButton->setEnabled(true);

        }
        conn.connClose();
     }
     else

            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}


void Dialog7::on_EntregarpushButton_clicked()
{
    MainWindow conn;
    QString id, nombre_pedido, fecha_pedido, fecha_entrega, especificaciones, detalles, costo, prioridad, id_cliente; //GUARDARE LA INFORMACION QUE INSERTE EN LOS LINE EDIT
    id = ui->IDPedidolineEdit->text();
    nombre_pedido = ui->NombrePedidolineEdit_2->text();
    fecha_pedido = ui->FechaPedidolineEdit_2->text();
    fecha_entrega = ui->FechaEntregalineEdit_2->text();
    especificaciones = ui->EspecificacionestextEdit_2->toPlainText();
    detalles = ui->DetallestextEdit_2->toPlainText();
    costo = ui->CostolineEdit_2->text();
    prioridad = ui->PrioridadlineEdit_2->text();
    id_cliente = ui->IDCLientelineEdit_2->text();
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("Delete  from pedido  where id = '"+id+"'" );

    if(qry.exec())
    {
        QMessageBox::information(this,tr("                       Entrega de Pedidos               "),tr("          El Pedido se ha entregado      "));
        ui->IDPedidolineEdit->clear();
        ui->NombrePedidolineEdit_2->clear();
        ui->FechaPedidolineEdit_2->clear();
        ui->FechaEntregalineEdit_2->clear();
        ui->EspecificacionestextEdit_2->clear();
        ui->DetallestextEdit_2->clear();
        ui->CostolineEdit_2->clear();
        ui->PrioridadlineEdit_2->clear();
        ui->IDCLientelineEdit_2->clear();
        ui->EntregarpushButton->setEnabled(false);

        conn.connClose();
        on_MostrarpushButton_clicked();
     }
     else
         QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}
