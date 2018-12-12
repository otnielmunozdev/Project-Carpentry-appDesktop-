#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include "mainwindow.h"
#include "dialog.h"
#include "dialog2.h"
#include "dialog3.h"
#include "dialog4.h"
#include "dialog6.h"

MainWindow1::MainWindow1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow1)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

MainWindow1::~MainWindow1()
{
    delete ui;
}

void MainWindow1::on_actionIngresar_3_triggered()
{
    Dialog *ventana = new Dialog(this);
    ventana->setModal(true);
    ventana->show();
    /*ventana->setVisible(true);
    ventana->hide();
    ventana->setVisible(false);*/

}

void MainWindow1::on_pushButton_2_clicked()
{
    Dialog *ventana = new Dialog(this);
    ventana->setModal(true);
    ventana->show();
}

void MainWindow1::on_pushButton_4_clicked()
{
    Dialog4 *ventana = new Dialog4(this);
    ventana->setModal(true);
    ventana->show();
}

void MainWindow1::on_pushButton_3_clicked()
{
    Dialog2 *ventana = new Dialog2(this);
    ventana->setModal(true);
    ventana->show();
}

void MainWindow1::on_actionOpciones_triggered()
{
    Dialog3 *ventana = new Dialog3(this);
    ventana->setModal(true);
    ventana->show();
}

void MainWindow1::on_actionOpciones_2_triggered()
{
    Dialog6 *ventana = new Dialog6(this);
    ventana->setModal(true);
    ventana->show();
}

void MainWindow1::on_pushButton_5_clicked()
{
    MainWindow *ventana3 = new MainWindow();
    ventana3->setVisible(true);
    this->setVisible(false);
}
