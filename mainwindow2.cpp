#include "mainwindow2.h"
#include "mainwindow.h"
#include "ui_mainwindow2.h"
#include "dialog7.h"

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

MainWindow2::~MainWindow2()
{
    delete ui;
}

void MainWindow2::on_PedidoClientepushButton_clicked()
{
    Dialog7 *ventana = new Dialog7(this);
    ventana->setModal(true);
    ventana->show();
}

void MainWindow2::on_pushButton_clicked()
{
    MainWindow *ventana3 = new MainWindow();
    ventana3->setVisible(true);
    this->setVisible(false);
}
