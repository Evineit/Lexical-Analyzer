#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include "iostream"
#include "QTextStream"
#include "cctype"

int states[21][31] = {
    {2, 1, 3, 506, 506, 2, 1, 105, 106, 107, 108, 128, 9, 10, 11, 12, 13, 14, 15, 119, 120, 121, 122, 123, 124, 17, 19, 0, 0, 0, 506},
    {2, 1, 2, 20, 100, 2, 1, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100},
    {2, 2, 2, 20, 101, 2, 1, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101},
    {102, 102, 3, 102, 4, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102},
    {500, 500, 5, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500},
    {103, 103, 5, 103, 103, 6, 6, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103},
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
    {19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 127, 19, 19, 19},
    {2, 2, 2, 508, 508, 2, 2, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508}};
QString reservedWords [32] = {"class", "endclass", "int", "float", "char", "string", "bool", "if", "else", "elseif", "endif", "do", "eval", "enddo", "while", "endwhile", "read", "write", "def", "as", "for", "endfor", "private", "public", "protected", "library", "func", "endfunc", "main", "endmain", "true", "false"};

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
    if (c.isUpper() && c != 'E')
        return 0;
    if (c.isLower() && c != 'e')
        return 1;
    if (c.isDigit())
        return 2;

    switch (c.unicode()) {
        case('_'):
            return 3;
        case('.'):
            return 4;
        case('E'):
            return 5;
        case('e'):
            return 6;
        case('+'):
            return 7;
        case('-'):
            return 8;
        case(10):
            return 27;
    }
    return 27;
}

void MainWindow::appendToken(int state, QString token){
    switch (state) {
        case(100):
            ui->textEdit_2->append("Estado de aceptacion 100: "+token+", Palabra reservada");
        break;
        case(101):
            ui->textEdit_2->append("Estado de aceptacion 101: "+token+", Identificador");
        break;
        case(102):
            ui->textEdit_2->append("Estado de aceptacion 102: "+token+", Entero");
        break;
        case(103):
            ui->textEdit_2->append("Estado de aceptacion 103: "+token+", Real");
        break;
        case(104):
            ui->textEdit_2->append("Estado de aceptacion 104: "+token+", N.Cientifica");
        break;
    }
}

void MainWindow::errorToken(int state){
    if (state == 500)
         ui->textEdit_3->setText("Error con estado: "+QString::number(state)+" Real incompleto");
    else if (state == 501)
         ui->textEdit_3->setText("Error con estado: "+QString::number(state)+" Notacion cientifica incompleta");
    else if (state == 502)
         ui->textEdit_3->setText("Error con estado: "+QString::number(state)+" Notacion cientifica incompleta");
    else if (state == 508)
         ui->textEdit_3->setText("Error con estado: "+QString::number(state)+" Identificador no puede terminar en '_'");
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
        state = states[state][relacionar(sourceText[i])];
        qInfo() << "Link:" << relacionar(sourceText[i]);
        qInfo() << "Token actual: " << token;
        qInfo() << "Simbolo actual: " << sourceText[i] << (int)sourceText[i].unicode();
        qInfo() << "Estado resultante:" << state<< "\n";
        if (state == 0)
            continue;
        else if (state <= 20){
            token.append(sourceText[i]);
        }
        else if (state >= 100 && state <= 128){
            if (state == 100 && !(std::find(std::begin(reservedWords), std::end(reservedWords), token) != std::end(reservedWords))){
                state = 101;
            }
            appendToken(state, token);
            token = "";
            state = 0;
        } else if(state >= 500) {
            errorToken(state);
            return;
        }
    }
    // EOT
    if (!token.isEmpty()) {
        state = states[state][relacionar(QChar(10))];
        qInfo() << "Simbolo actual: EOT" << (int)QChar(10).unicode();
        qInfo() << "Estado resultante:" << state;
        if (state >= 100 && state <= 128){
            if (state == 100 && !(std::find(std::begin(reservedWords), std::end(reservedWords), token) != std::end(reservedWords))){
                state = 101;
            }
            appendToken(state, token);
        } else if(state >= 500) {
            errorToken(state);
        }
    }
}

