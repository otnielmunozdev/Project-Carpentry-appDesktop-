#include "dialog.h"
#include "ui_dialog.h"
#include "dialog5.h"
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

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE"); // CREO EL OBJETO DE TIPO BD Y LE IMPORTO EL SQLITE
    mydb.setDatabaseName("MAC.db"); //DIRECCION DE LA BD
    if(!mydb.open())//SI ESTA DESCONECTADA LA BD DEL SISTEMA
        ui->Statuslabel->setText(" No Conectada......");
    else
        ui->Statuslabel->setText("Conectada a la base de datos.....");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::Habilitar()
{
    if(ui->NombrePedidolineEdit->text().length() > 0 && ui->FechaPedidolineEdit->text().length() > 0 && ui->FechaEntregalineEdit->text().length() > 0 && ui->EspecificacionestextEdit->toPlainText().length() > 0 &&  ui->DetallestextEdit->toPlainText().length() > 0 &&  ui->CostolineEdit->text().length() > 0 &&  ui->PrioridadlineEdit->text().length() > 0 &&  ui->IDCLientelineEdit->text().length() > 0 )
    {
        ui->RegistrarpushButton->setEnabled(true);
    }
    else
    {
        ui->RegistrarpushButton->setEnabled(false);
    }
}

void Dialog::on_FechaPedidolineEdit_textChanged(const QString &arg1)
{
    Habilitar();
}

void Dialog::on_FechaEntregalineEdit_textChanged(const QString &arg1)
{
    Habilitar();
}

void Dialog::on_EspecificacionestextEdit_textChanged()
{
    Habilitar();
}

void Dialog::on_DetallestextEdit_textChanged()
{
    Habilitar();
}


void Dialog::on_NombrePedidolineEdit_textChanged(const QString &arg1)
{
    Habilitar();
}

void Dialog::on_CostolineEdit_textChanged(const QString &arg1)
{
    Habilitar();
}

void Dialog::on_PrioridadlineEdit_textChanged(const QString &arg1)
{
    Habilitar();
}

void Dialog::on_IDCLientelineEdit_textChanged(const QString &arg1)
{
    Habilitar();
}


void Dialog::on_RegistrarpushButton_clicked()
{
    MainWindow conn; //CREO UNA INSTANCIA DE LA CLASE MAINWINDOWS DONDE TENDRE EL CONTROL PARA LLAMAR LOS METODOS
    QString  nombre_pedido, fecha_pedido, fecha_entrega, especificaciones, detalles, costo, prioridad, id_cliente; //GUARDARE LA INFORMACION QUE INSERTE EN LOS LINE EDIT
    nombre_pedido = ui->NombrePedidolineEdit->text();
    fecha_pedido = ui->FechaPedidolineEdit->text();
    fecha_entrega = ui->FechaEntregalineEdit->text();
    especificaciones = ui->EspecificacionestextEdit->toPlainText();
    detalles = ui->DetallestextEdit->toPlainText();
    costo = ui->CostolineEdit->text();
    prioridad = ui->PrioridadlineEdit->text();
    id_cliente = ui->IDCLientelineEdit->text();

    conn.connOpen();//ABRO MI BD
    QSqlQuery qry, qry2; //INSERTO LOS DATOS A LA BD
    qry.prepare("insert into pedido (nombre_pedido, fecha_pedido, fecha_entrega, especificaciones, detalles, costo, prioridad, id_cliente) values ('"+nombre_pedido+"', '"+fecha_pedido+"','"+fecha_entrega+"','"+especificaciones+"','"+detalles+"','"+costo+"','"+prioridad+"','"+id_cliente+"')");
    qry2.prepare("insert into pedido_costo (nombre_pedido, costo, fecha_pedido, fecha_entrega) values ('"+nombre_pedido+"','"+costo+"','"+fecha_pedido+"','"+fecha_entrega+"')");

    if(qry.exec()&&qry2.exec())//SI LA BD ESTA CONECTADA Y SE GUARDA LA INFO BIEN
    {
        QMessageBox::information(this,tr(".......................Save...................!!"),tr("     !!Los datos se guardaron!!     "));
         ui->NombrePedidolineEdit->clear();
         ui->FechaPedidolineEdit->clear();
         ui->FechaEntregalineEdit->clear();
         ui->EspecificacionestextEdit->clear();
         ui->DetallestextEdit->clear();
         ui->CostolineEdit->clear();
         ui->PrioridadlineEdit->clear();
         ui->IDCLientelineEdit->clear();

        conn.connClose();
        on_MostrarAltapushButton_clicked();
        on_MostrarpushButton_clicked();
        on_MostrarBajapushButton_clicked();
        on_MostrarMediapushButton_clicked();
     }
     else

            QMessageBox::critical(this,tr("error::"),qry.lastError().text());

}

void Dialog::on_MostrarpushButton_clicked()
{
    //QString x= "Ninguno";
    MainWindow conn; //CREO UN OBJETO DE LA CLASE MAINWINDOWS DONDE TENDRE EL CONTROL PARA LLAMR LOS METODOS
    QSqlQueryModel * modal = new QSqlQueryModel(); //hará referencia a las distintas columnas por el nombre del role establecido en el modelo.

    conn.connOpen();//ABRO LA BD
    QSqlQuery * qry=new QSqlQuery(conn.mydb);//CREO UN NUEVO QRY DONDE LO CONECTARE CON MY DB Y SELECCIONO LA INFORMACION DE LA BD
    qry->prepare("SELECT * from pedido");
    //qry->prepare("SELECT  id, nombre_cliente, fecha_pedido, fecha_entrega, especificaciones, detalles from pedido where detalles = '"%x%"'");

    qry->exec();
    modal->setQuery(*qry);//METO A LA TABLA TODO LO QUE HAY EN QRY
    ui->tableView->setModel(modal);//ACOMODARA COMO TABLA SIN NECESIDAD DE UN SIZE
    conn.connClose();//CIERRO MI BD

    qDebug() << (modal->rowCount());//MUESTRA EN CONSOLA EL NUMERO DE COLUMNAS
}


void Dialog::on_ClientepushButton_clicked()
{
    Dialog5 *ventana = new Dialog5(this);
    ventana->setModal(true);
    ventana->show();
}

void Dialog::on_BuscarpushButton_clicked()
{
    QString buscar=ui->BuscarlineEdit->text();
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from pedido WHERE  nombre_pedido = '"+buscar+"' or fecha_pedido = '"+buscar+"' or fecha_entrega = '"+ buscar+"' or especificaciones = '"+ buscar+"' or detalles = '"+ buscar+"' or costo = '"+ buscar+"' or id_cliente = '"+ buscar+"'");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}

void Dialog::on_BuscarAltapushButton_clicked()
{
    QString buscar=ui->BuscarAltalineEdit->text();
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from pedido WHERE  nombre_pedido = '"+buscar+"' or fecha_pedido = '"+buscar+"' or fecha_entrega = '"+ buscar+"' or especificaciones = '"+ buscar+"' or detalles = '"+ buscar+"' or costo = '"+ buscar+"' or id_cliente = '"+ buscar+"'");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_2->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}



void Dialog::on_BuscarMediapushButton_clicked()
{
    QString buscar=ui->BuscarMedialineEdit->text();
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from pedido WHERE  nombre_pedido = '"+buscar+"' or fecha_pedido = '"+buscar+"' or fecha_entrega = '"+ buscar+"' or especificaciones = '"+ buscar+"' or detalles = '"+ buscar+"' or costo = '"+ buscar+"' or id_cliente = '"+ buscar+"'");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_3->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}


void Dialog::on_BuscarBajapushButton_clicked()
{
    QString buscar=ui->BuscarBajalineEdit->text();
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from pedido WHERE  nombre_pedido = '"+buscar+"' or fecha_pedido = '"+buscar+"' or fecha_entrega = '"+ buscar+"' or especificaciones = '"+ buscar+"' or detalles = '"+ buscar+"' or costo = '"+ buscar+"' or id_cliente = '"+ buscar+"'");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_4->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}


void Dialog::on_MostrarAltapushButton_clicked()
{
    QString x= "Alta";
    QString y= "alta";
    MainWindow conn; //CREO UN OBJETO DE LA CLASE MAINWINDOWS DONDE TENDRE EL CONTROL PARA LLAMR LOS METODOS
    QSqlQueryModel * modal = new QSqlQueryModel(); //hará referencia a las distintas columnas por el nombre del role establecido en el modelo.

    conn.connOpen();//ABRO LA BD
    QSqlQuery * qry=new QSqlQuery(conn.mydb);//CREO UN NUEVO QRY DONDE LO CONECTARE CON MY DB Y SELECCIONO LA INFORMACION DE LA BD
    qry->prepare("SELECT id, nombre_pedido, fecha_pedido, fecha_entrega, especificaciones, detalles, costo, prioridad, id_cliente from pedido where prioridad = '"%x%"' or '"%y%"'");

    qry->exec();
    modal->setQuery(*qry);//METO A LA TABLA TODO LO QUE HAY EN QRY
    ui->tableView_2->setModel(modal);//ACOMODARA COMO TABLA SIN NECESIDAD DE UN SIZE
    conn.connClose();//CIERRO MI BD

    qDebug() << (modal->rowCount());//MUESTRA EN CONSOLA EL NUMERO DE COLUMNAS
}

void Dialog::on_MostrarMediapushButton_clicked()
{
    QString x= "Media";
    QString y= "media";
    MainWindow conn; //CREO UN OBJETO DE LA CLASE MAINWINDOWS DONDE TENDRE EL CONTROL PARA LLAMR LOS METODOS
    QSqlQueryModel * modal = new QSqlQueryModel(); //hará referencia a las distintas columnas por el nombre del role establecido en el modelo.

    conn.connOpen();//ABRO LA BD
    QSqlQuery * qry=new QSqlQuery(conn.mydb);//CREO UN NUEVO QRY DONDE LO CONECTARE CON MY DB Y SELECCIONO LA INFORMACION DE LA BD
    qry->prepare("SELECT id, nombre_pedido, fecha_pedido, fecha_entrega, especificaciones, detalles, costo, prioridad, id_cliente from pedido where prioridad = '"%x%"' or '"%y%"'");

    qry->exec();
    modal->setQuery(*qry);//METO A LA TABLA TODO LO QUE HAY EN QRY
    ui->tableView_3->setModel(modal);//ACOMODARA COMO TABLA SIN NECESIDAD DE UN SIZE
    conn.connClose();//CIERRO MI BD

    qDebug() << (modal->rowCount());//MUESTRA EN CONSOLA EL NUMERO DE COLUMNAS
}

void Dialog::on_MostrarBajapushButton_clicked()
{
    QString x= "Baja";
    QString y= "baja";
    MainWindow conn; //CREO UN OBJETO DE LA CLASE MAINWINDOWS DONDE TENDRE EL CONTROL PARA LLAMR LOS METODOS
    QSqlQueryModel * modal = new QSqlQueryModel(); //hará referencia a las distintas columnas por el nombre del role establecido en el modelo.

    conn.connOpen();//ABRO LA BD
    QSqlQuery * qry=new QSqlQuery(conn.mydb);//CREO UN NUEVO QRY DONDE LO CONECTARE CON MY DB Y SELECCIONO LA INFORMACION DE LA BD
    qry->prepare("SELECT id, nombre_pedido, fecha_pedido, fecha_entrega, especificaciones, detalles, costo, prioridad, id_cliente from pedido where prioridad = '"%x%"' or '"%y%"'");

    qry->exec();
    modal->setQuery(*qry);//METO A LA TABLA TODO LO QUE HAY EN QRY
    ui->tableView_4->setModel(modal);//ACOMODARA COMO TABLA SIN NECESIDAD DE UN SIZE
    conn.connClose();//CIERRO MI BD

    qDebug() << (modal->rowCount());//MUESTRA EN CONSOLA EL NUMERO DE COLUMNAS
}



void Dialog::on_tableView_activated(const QModelIndex &index)
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
            ui->ModificarpushButton->setEnabled(true);
            ui->EliminarpushButton->setEnabled(true);
            ui->NombrePedidolineEdit_2->setEnabled(true);
            ui->FechaPedidolineEdit_2->setEnabled(true);
            ui->FechaEntregalineEdit_2->setEnabled(true);
            ui->EspecificacionestextEdit_2->setEnabled(true);
            ui->DetallestextEdit_2->setEnabled(true);
            ui->CostolineEdit_2->setEnabled(true);
            ui->PrioridadlineEdit_2->setEnabled(true);
            ui->IDCLientelineEdit_2->setEnabled(true);
        }
        conn.connClose();
     }
     else

            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}


void Dialog::on_tableView_2_activated(const QModelIndex &index)
{
    MainWindow conn;
    QString val = ui->tableView_2->model()->data(index).toString();

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
         //QMessageBox::information(this,tr("                    Activado                    "),tr("     Los datos se han activado se pueden modificar o eliminar     "));
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
            ui->ModificarpushButton->setEnabled(true);
            ui->EliminarpushButton->setEnabled(true);
            ui->NombrePedidolineEdit_2->setEnabled(true);
            ui->FechaPedidolineEdit_2->setEnabled(true);
            ui->FechaEntregalineEdit_2->setEnabled(true);
            ui->EspecificacionestextEdit_2->setEnabled(true);
            ui->DetallestextEdit_2->setEnabled(true);
            ui->CostolineEdit_2->setEnabled(true);
            ui->PrioridadlineEdit_2->setEnabled(true);
            ui->IDCLientelineEdit_2->setEnabled(true);
        }
        conn.connClose();
     }
     else

            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void Dialog::on_tableView_3_activated(const QModelIndex &index)
{
    MainWindow conn;
    QString val = ui->tableView_3->model()->data(index).toString();

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
         //QMessageBox::information(this,tr("                    Activado                    "),tr("     Los datos se han activado se pueden modificar o eliminar     "));
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
            ui->ModificarpushButton->setEnabled(true);
            ui->EliminarpushButton->setEnabled(true);
            ui->NombrePedidolineEdit_2->setEnabled(true);
            ui->FechaPedidolineEdit_2->setEnabled(true);
            ui->FechaEntregalineEdit_2->setEnabled(true);
            ui->EspecificacionestextEdit_2->setEnabled(true);
            ui->DetallestextEdit_2->setEnabled(true);
            ui->CostolineEdit_2->setEnabled(true);
            ui->PrioridadlineEdit_2->setEnabled(true);
            ui->IDCLientelineEdit_2->setEnabled(true);
        }
        conn.connClose();
     }
     else

            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void Dialog::on_tableView_4_activated(const QModelIndex &index)
{
    MainWindow conn;
    QString val = ui->tableView_4->model()->data(index).toString();

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
         //QMessageBox::information(this,tr("                    Activado                    "),tr("     Los datos se han activado se pueden modificar o eliminar     "));
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
            ui->ModificarpushButton->setEnabled(true);
            ui->EliminarpushButton->setEnabled(true);
            ui->NombrePedidolineEdit_2->setEnabled(true);
            ui->FechaPedidolineEdit_2->setEnabled(true);
            ui->FechaEntregalineEdit_2->setEnabled(true);
            ui->EspecificacionestextEdit_2->setEnabled(true);
            ui->DetallestextEdit_2->setEnabled(true);
            ui->CostolineEdit_2->setEnabled(true);
            ui->PrioridadlineEdit_2->setEnabled(true);
            ui->IDCLientelineEdit_2->setEnabled(true);
        }
        conn.connClose();
     }
     else

            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}



void Dialog::on_ModificarpushButton_clicked()
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
    QSqlQuery qry, qry2;
    qry.prepare("update pedido set nombre_pedido = '"+nombre_pedido+"', fecha_pedido = '"+fecha_pedido+"', fecha_entrega = '"+fecha_entrega+"' , especificaciones = '"+especificaciones+"', detalles = '"+detalles+"',  costo = '"+costo+"', prioridad = '"+prioridad+"', id_cliente = '"+id_cliente+"'  where id ='"+id+"'" );
    qry2.prepare("update pedido_costo set nombre_pedido = '"+nombre_pedido+"', costo = '"+costo+"', fecha_pedido = '"+fecha_pedido+"', fecha_entrega = '"+fecha_entrega+"'  where id ='"+id+"'" );

    if(qry.exec() && qry2.exec())
    {
        QMessageBox::information(this,tr("                       Pedidos               "),tr("          El Pedido se ha modificado correctamente     "));
        ui->IDPedidolineEdit->clear();
        ui->NombrePedidolineEdit_2->clear();
        ui->FechaPedidolineEdit_2->clear();
        ui->FechaEntregalineEdit_2->clear();
        ui->EspecificacionestextEdit_2->clear();
        ui->DetallestextEdit_2->clear();
        ui->CostolineEdit_2->clear();
        ui->PrioridadlineEdit_2->clear();
        ui->IDCLientelineEdit_2->clear();
        ui->ModificarpushButton->setEnabled(false);
        ui->EliminarpushButton->setEnabled(false);
        ui->NombrePedidolineEdit_2->setEnabled(false);
        ui->FechaPedidolineEdit_2->setEnabled(false);
        ui->FechaEntregalineEdit_2->setEnabled(false);
        ui->EspecificacionestextEdit_2->setEnabled(false);
        ui->DetallestextEdit_2->setEnabled(false);
        ui->CostolineEdit_2->setEnabled(false);
        ui->PrioridadlineEdit_2->setEnabled(false);
        ui->IDCLientelineEdit_2->setEnabled(false);
        conn.connClose();
        on_MostrarAltapushButton_clicked();
        on_MostrarpushButton_clicked();
        on_MostrarBajapushButton_clicked();
        on_MostrarMediapushButton_clicked();
     }
     else
         QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}


void Dialog::on_EliminarpushButton_clicked()
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
        QMessageBox::information(this,tr("                       Pedidos               "),tr("          El Pedido se ha eliminado correctamente     "));
        ui->IDPedidolineEdit->clear();
        ui->NombrePedidolineEdit_2->clear();
        ui->FechaPedidolineEdit_2->clear();
        ui->FechaEntregalineEdit_2->clear();
        ui->EspecificacionestextEdit_2->clear();
        ui->DetallestextEdit_2->clear();
        ui->CostolineEdit_2->clear();
        ui->PrioridadlineEdit_2->clear();
        ui->IDCLientelineEdit_2->clear();
        ui->ModificarpushButton->setEnabled(false);
        ui->EliminarpushButton->setEnabled(false);
        ui->NombrePedidolineEdit_2->setEnabled(false);
        ui->FechaPedidolineEdit_2->setEnabled(false);
        ui->FechaEntregalineEdit_2->setEnabled(false);
        ui->EspecificacionestextEdit_2->setEnabled(false);
        ui->DetallestextEdit_2->setEnabled(false);
        ui->CostolineEdit_2->setEnabled(false);
        ui->PrioridadlineEdit_2->setEnabled(false);
        ui->IDCLientelineEdit_2->setEnabled(false);
        conn.connClose();
        on_MostrarAltapushButton_clicked();
        on_MostrarpushButton_clicked();
        on_MostrarBajapushButton_clicked();
        on_MostrarMediapushButton_clicked();
     }
     else
         QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}
