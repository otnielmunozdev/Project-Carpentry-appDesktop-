#include "dialog4.h"
#include "ui_dialog4.h"
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

Dialog4::Dialog4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog4)
{
    ui->setupUi(this);
}

Dialog4::~Dialog4()
{
    delete ui;
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE"); // CREO EL OBJETO DE TIPO BD Y LE IMPORTO EL SQLITE
    mydb.setDatabaseName("MAC.db"); //DIRECCION DE LA BD

}

void Dialog4::Habilitar4()
{
    if(ui->NombreDistribuidorlineEdit->text().length() > 0 && ui->NumeroDistribuidorlineEdit->text().length() > 0 && ui->TipoServiciodistribuidorlineEdit->text().length() > 0 )
    {
        ui->RegistrarpushButton->setEnabled(true);
    }
    else
    {
        ui->RegistrarpushButton->setEnabled(false);
    }
}

void Dialog4::Habilitar4_1()
{
    if(ui->NombreDistribuidorEMlineEdit->text().length() > 0 && ui->NumeroDistribuidorEMlineEdit->text().length() > 0 && ui->TipoServiciodistribuidorEMlineEdit->text().length() > 0 )
    {
        ui->ModificarDistribuidorpushButton->setEnabled(true);
        ui->EliminarDistribuidorpushButton->setEnabled(true);
    }
    else
    {
        ui->ModificarDistribuidorpushButton->setEnabled(false);
        ui->EliminarDistribuidorpushButton->setEnabled(false);
    }
}

void Dialog4::on_NombreDistribuidorEMlineEdit_textChanged(const QString &arg1)
{
     Habilitar4_1();
}

void Dialog4::on_NumeroDistribuidorEMlineEdit_textChanged(const QString &arg1)
{
     Habilitar4_1();
}

void Dialog4::on_TipoServiciodistribuidorEMlineEdit_textChanged(const QString &arg1)
{
    Habilitar4_1();
}

void Dialog4::on_NombreDistribuidorlineEdit_textChanged(const QString &arg1)
{
    Habilitar4();
}

void Dialog4::on_NumeroDistribuidorlineEdit_textChanged(const QString &arg1)
{
    Habilitar4();
}

void Dialog4::on_TipoServiciodistribuidorlineEdit_textChanged(const QString &arg1)
{
    Habilitar4();
}


void Dialog4::on_RegistrarpushButton_clicked()
{
    MainWindow conn; //CREO UNA INSTANCIA DE LA CLASE MAINWINDOWS DONDE TENDRE EL CONTROL PARA LLAMAR LOS METODOS
    QString  nombre, num_distribuidor, tipo_distribuidor; //GUARDARE LA INFORMACION QUE INSERTE EN LOS LINE EDIT
    nombre = ui->NombreDistribuidorlineEdit->text();
    num_distribuidor = ui->NumeroDistribuidorlineEdit->text();
    tipo_distribuidor = ui->TipoServiciodistribuidorlineEdit->text();

    conn.connOpen();//ABRO MI BD
    QSqlQuery qry; //INSERTO LOS DATOS A LA BD
    qry.prepare("insert into distribuidores (nombre, num_distribuidor, tipo_distribuidor) values ('"+nombre+"', '"+num_distribuidor+"','"+tipo_distribuidor+"')");

    if(qry.exec())//SI LA BD ESTA CONECTADA Y SE GUARDA LA INFO BIEN
    {
        QMessageBox::information(this,tr(".......................Save...................!!"),tr("     !!Los datos se guardaron!!     "));
         ui->NombreDistribuidorlineEdit->clear();
         ui->NumeroDistribuidorlineEdit->clear();
         ui->TipoServiciodistribuidorlineEdit->clear();

        conn.connClose();
        on_MostrarDistribuidorpushButton_clicked();
     }
     else

            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}
void Dialog4::on_MostrarDistribuidorpushButton_clicked()
{
    MainWindow conn; //CREO UN OBJETO DE LA CLASE MAINWINDOWS DONDE TENDRE EL CONTROL PARA LLAMR LOS METODOS
    QSqlQueryModel * modal = new QSqlQueryModel(); //hará referencia a las distintas columnas por el nombre del role establecido en el modelo.

    conn.connOpen();//ABRO LA BD
    QSqlQuery * qry=new QSqlQuery(conn.mydb);//CREO UN NUEVO QRY DONDE LO CONECTARE CON MY DB Y SELECCIONO LA INFORMACION DE LA BD

    qry->prepare("SELECT * from distribuidores");

    qry->exec();
    modal->setQuery(*qry);//METO A LA TABLA TODO LO QUE HAY EN QRY
    ui->tableView->setModel(modal);//ACOMODARA COMO TABLA SIN NECESIDAD DE UN SIZE
    conn.connClose();//CIERRO MI BD

    qDebug() << (modal->rowCount());//MUESTRA EN CONSOLA EL NUMERO DE COLUMNAS
}



void Dialog4::on_BuscarpushButton_clicked()
{
    QString buscar=ui->BuscarlineEdit->text();
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from distribuidores WHERE  id = '"+buscar+"' or nombre = '"+buscar+"' or num_distribuidor = '"+buscar+"' or tipo_distribuidor = '"+ buscar+"'");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    conn.connClose();

    qDebug() << (modal->rowCount());
}



void Dialog4::on_tableView_activated(const QModelIndex &index)
{
    QString val = ui->tableView->model()->data(index).toString();

    MainWindow conn;
    QString  id, nombre, num_distribuidor, tipo_distribuidor;
    id = ui->IDdistribuidoreslineEdit->text();
    nombre = ui->NombreDistribuidorEMlineEdit->text();
    num_distribuidor = ui->NumeroDistribuidorEMlineEdit->text();
    tipo_distribuidor = ui->TipoServiciodistribuidorEMlineEdit->text();

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from distribuidores WHERE id='"+val+"' or nombre = '"+val+"' or num_distribuidor = '"+val+"' or tipo_distribuidor = '"+val+"'");

    if(qry.exec())
    {
        // QMessageBox::information(this,tr("                    Activado                    "),tr("     Los datos se han activado se pueden modificar o eliminar     "));
        while(qry.next())
        {
            ui->IDdistribuidoreslineEdit->setText(qry.value(0).toString());
            ui->NombreDistribuidorEMlineEdit->setText(qry.value(1).toString());
            ui->NumeroDistribuidorEMlineEdit->setText(qry.value(2).toString());
            ui->TipoServiciodistribuidorEMlineEdit->setText(qry.value(3).toString());
            ui->ModificarDistribuidorpushButton->setEnabled(true);
            ui->EliminarDistribuidorpushButton->setEnabled(true);
            ui->NombreDistribuidorEMlineEdit->setEnabled(true);
            ui->NumeroDistribuidorEMlineEdit->setEnabled(true);
            ui->TipoServiciodistribuidorEMlineEdit->setEnabled(true);
        }
        conn.connClose();
     }
     else

            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void Dialog4::on_ModificarDistribuidorpushButton_clicked()
{
    MainWindow conn;
    QString  id, nombre, num_distribuidor, tipo_distribuidor;
    id = ui->IDdistribuidoreslineEdit->text();
    nombre = ui->NombreDistribuidorEMlineEdit->text();
    num_distribuidor = ui->NumeroDistribuidorEMlineEdit->text();
    tipo_distribuidor = ui->TipoServiciodistribuidorEMlineEdit->text();
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update distribuidores set nombre = '"+nombre+"', num_distribuidor = '"+num_distribuidor+"', tipo_distribuidor = '"+tipo_distribuidor+"' where id ='"+id+"'" );

    if(qry.exec())
    {
        QMessageBox::information(this,tr("                       Distribuidores               "),tr("          El distribuidor se ha modificado correctamente     "));
        ui->IDdistribuidoreslineEdit->clear();
        ui->NombreDistribuidorEMlineEdit->clear();
        ui->NumeroDistribuidorEMlineEdit->clear();
        ui->TipoServiciodistribuidorEMlineEdit->clear();
        ui->EliminarDistribuidorpushButton->setEnabled(false);
        ui->ModificarDistribuidorpushButton->setEnabled(false);
        ui->NombreDistribuidorEMlineEdit->setEnabled(false);
        ui->NumeroDistribuidorEMlineEdit->setEnabled(false);
        ui->TipoServiciodistribuidorEMlineEdit->setEnabled(false);
        conn.connClose();
        on_MostrarDistribuidorpushButton_clicked();
     }
     else
         QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void Dialog4::on_EliminarDistribuidorpushButton_clicked()
{
    MainWindow conn;
    QString  id, nombre, num_distribuidor, tipo_distribuidor;
    id = ui->IDdistribuidoreslineEdit->text();
    nombre = ui->NombreDistribuidorEMlineEdit->text();
    num_distribuidor = ui->NumeroDistribuidorEMlineEdit->text();
    tipo_distribuidor = ui->TipoServiciodistribuidorEMlineEdit->text();

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("Delete from distribuidores where id = '"+id+"'" );

    if(qry.exec())
    {
        QMessageBox::information(this,tr("                       Distribuidores               "),tr("          El distribuidor se ha eliminado correctamente     "));
        ui->IDdistribuidoreslineEdit->clear();
        ui->NombreDistribuidorEMlineEdit->clear();
        ui->NumeroDistribuidorEMlineEdit->clear();
        ui->TipoServiciodistribuidorEMlineEdit->clear();
        ui->EliminarDistribuidorpushButton->setEnabled(false);
        ui->ModificarDistribuidorpushButton->setEnabled(false);
        ui->NombreDistribuidorEMlineEdit->setEnabled(false);
        ui->NumeroDistribuidorEMlineEdit->setEnabled(false);
        ui->TipoServiciodistribuidorEMlineEdit->setEnabled(false);
        conn.connClose();
        on_MostrarDistribuidorpushButton_clicked();
     }
     else
         QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}


