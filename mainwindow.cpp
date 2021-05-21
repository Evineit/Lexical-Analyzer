#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include "iostream"
#include "QTextStream"
#include "cctype"

int states[20][31] = {
    {2, 1, 3, 506, 506, 2, 1, 105, 106, 107, 108, 128, 9, 10, 11, 12, 13, 14, 15, 119, 120, 121, 122, 123, 124, 17, 19, 0, 0, 0, 506},
    {2, 1, 2, 2, 100, 2, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100},
    {2, 2, 2, 2, 101, 2, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101},
    {102, 102, 3, 102, 4, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102},
    {500, 500, 5, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500},
    {103, 103, 5, 103, 103, 103, 6, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103},
    {501, 501, 8, 501, 501, 501, 501, 7, 7, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501},
    {502, 502, 8, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502},
    {104, 104, 8, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104},
    {109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 110, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109},
    {111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 112, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111},
    {113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 114, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113},
    {116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 115, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116},
    {503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 117, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503},
    {504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 118, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504},
    {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 505, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16},
    {507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 125, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507},
    {17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 17, 17, 17, 17, 17},
    {126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 17, 126, 126, 126, 126, 126},
    {19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 127, 19, 19, 19}};

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

int MainWindow::relacionar(QChar c){
    if (c.isUpper())
        return 0;
    if (c.isLower())
        return 1;
    if (c.isDigit())
        return 2;

    switch (c.unicode()) {
        case('.'):
            return 4;
        case(10):
            return 27;
    }
    return 0;
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

void MainWindow::on_analizarButton_clicked()
{
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
    int state = 0;
    QString token = "";
    QString sourceText = ui->textEdit->toPlainText();
    for (int i = 0;i < sourceText.size() ; i++ ) {
        qInfo() << "Link:" << relacionar(sourceText[i]);
        state = states[state][relacionar(sourceText[i])];
        qInfo() << "Token actual: " << token;
        qInfo() << "Simbolo actual: " << sourceText[i] << (int)sourceText[i].unicode();
        qInfo() << "Estado resultante:" << state<< "\n";
        if (state == 0)
            continue;
        if (!(state == 102 || state == 103)){
            token.append(sourceText[i]);
        }
        if (state == 102){
            ui->textEdit_2->append("Estado de aceptacion 102: "+token+", Entero");
            token = "";
            state = 0;
        } else if(state == 103){
            ui->textEdit_2->append("Estado de aceptacion 103: "+token+", Real");
            token = "";
            state = 0;
        } else if(state >= 500) {
            ui->textEdit_2->setText("Error con estado: "+QString::number(state));
        }
    }
    // EOT
    if (!token.isEmpty()) {
        state = states[state][relacionar(QChar(10))];
        qInfo() << "simbolo actual: EOT" << (int)QChar(10).unicode();
        qInfo() << "Estado resultante:" << state;
        switch (state) {
            case(102):
                ui->textEdit_2->append("Estado de aceptacion 102: "+token+", Entero");
            break;
            case(103):
                ui->textEdit_2->append("Estado de aceptacion 103: "+token+", Real");
            break;
            case(500):
                ui->textEdit_3->setText("Error con estado: "+QString::number(state));
            break;
        }
    }
}

