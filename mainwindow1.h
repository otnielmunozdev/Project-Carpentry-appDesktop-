#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QMainWindow>
#include <dialog.h>

namespace Ui {
class MainWindow1;
}

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(QWidget *parent = 0);
    ~MainWindow1();
    void Habilitar();

signals:
    void back();

private slots:
    void on_actionIngresar_3_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_actionOpciones_triggered();

    void on_actionOpciones_2_triggered();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow1 *ui;
};

#endif // MAINWINDOW1_H
