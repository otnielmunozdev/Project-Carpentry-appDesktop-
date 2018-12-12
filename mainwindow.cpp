#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QVector>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QtWidgets>
#include <QStringList>
#include <QList>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>
#include <QDebug>
#include <QtAlgorithms>
#include <QFile>
#include <fstream>
#include <stdio.h>
#include <QToolBar>
#include <QHash>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    ventana = new MainWindow1();
    ventana2 = new MainWindow2();
}

void MainWindow::esconder()
{
    this->setVisible(true);
    ventana->setVisible(false);
    QObject::connect(ventana, SIGNAL(back()), this, SLOT(esconder()));
    ventana2->setVisible(false);
    QObject::connect(ventana2, SIGNAL(back()), this, SLOT(esconder()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_IngresarpushButton_clicked()
{
    QString x = "admin";
    QString y = "admin";
    QString a = "empleado";
    QString b = "empleado";

    if(ui->UserNamelineEdit->text()  == x && ui->PasswordlineEdit->text()== y)
    {
        QMessageBox::information(this,tr("                            BIENVENIDO ADMINISTRADOR                           "),tr("     Accediendo al programa de la carpinteria      "));
        this->setVisible(false);
        ventana->setVisible(true);

    }

    else if(ui->UserNamelineEdit->text()  == a && ui->PasswordlineEdit->text()== b)
    {
        QMessageBox::information(this,tr("                            BIENVENIDO EMPLEADO                          "),tr("     Accediendo al programa de la carpinteria      "));
        this->setVisible(false);
        ventana2->setVisible(true);

    }
    else
    {
        QMessageBox::critical(this,tr(".......................ERROR...................!!"),tr("     !!    INTRODUZCA DATOS CORRECTOS    !!     "));

    }
}
