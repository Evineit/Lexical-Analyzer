#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include "iostream"
#include "QTextStream"

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


void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Abrir archivo","~/",tr("Archivo Spes (*.spes)"));
    if (fileName.isEmpty()){
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::warning(this, "Error ", file.errorString());
        return;
    }
    ui->textEdit->setText(file.readAll());
    file.close();
}


void MainWindow::on_pushButton_4_clicked()
{
    qApp->closeAllWindows();
}
