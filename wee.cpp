#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_agregarButton_clicked()
{
    QString producto = ui->productoLineEdit->text();
    double precio = ui->precioSpinBox->value();

    QString texto = producto + " - $" + QString::number(precio);
    ui->listaProductos->addItem(texto);
}


void MainWindow::on_agregarButton_clicked()
{
    QString producto = ui->productoLineEdit->text();
    double precio = ui->precioSpinBox->value();

    QString texto = producto + " - $" + QString::number(precio);
    ui->listaProductos->addItem(texto);
}


