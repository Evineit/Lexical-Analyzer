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
    QFile file;
    QTextStream io;
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,"Abrir archivo",tr("*.spes"));

    if (fileName.isEmpty()){
        return;
    }
    file.setFileName(fileName);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    if (!file.isOpen()){
        QMessageBox::critical(this, "Error ", file.errorString());
        return;
    }
    io.setDevice(&file);
    ui->textEdit->setText(io.readAll());
    file.flush();
    file.close();
}


void MainWindow::on_pushButton_4_clicked()
{
    qApp->closeAllWindows();
}
