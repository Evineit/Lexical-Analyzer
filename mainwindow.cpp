#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include "iostream"
#include "QTextStream"
#include "cctype"

int states[29][31] = {
	{2, 1, 3, 506, 28, 2, 1, 21, 22, 23, 24, 25, 9, 10, 11, 12, 13, 14, 15, 119, 120, 121, 122, 123, 124, 17, 19, 0, 0, 0, 506},
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
	{126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126},
	{19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 127, 19, 19, 19},
	{2, 2, 2, 508, 508, 2, 2, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508},
	{105, 105, 105, 105, 105, 105, 105, 129, 105, 105, 105, 105, 132, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105},
	{106, 106, 106, 106, 106, 106, 106, 106, 130, 106, 106, 106, 133, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106},
	{107, 107, 107, 107, 107, 107, 107, 107, 107, 131, 107, 107, 134, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107},
	{108, 108, 108, 108, 108, 108, 108, 108, 108, 26, 108, 108, 135, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108},
	{128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 136, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
	{26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26},
	{26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 137, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26},
	{506, 506, 506, 506, 138, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506}};

int autoConclusiveStates [] = {110,112,114,115,117,118,119,120,121,122,123,124,125,129,130,131,132,133,134,135,136,137,138};
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
        case('*'):
            return 9;
        case('/'):
            return 10;
        case('%'):
            return 11;
        case('='):
            return 12;
        case('<'):
            return 13;
        case('>'):
            return 14;
        case('!'):
            return 15;
        case('&'):
            return 16;
        case('|'):
            return 17;
        case('\''):
            return 18;
        case('('):
            return 19;
        case(')'):
            return 20;
        case('['):
            return 21;
        case(']'):
            return 22;
        case(';'):
            return 23;
        case(','):
            return 24;
        case('\"'):
            return 25;
        case('#'):
            return 26;
        case(10):
            return 27;
        case('\t'):
            return 28;
        case(32):
            return 29;
    }
    return 30;
}

void MainWindow::appendToken(int state, QString token){
    switch (state) {
        case(100):
            ui->textEdit_2->append("Estado de aceptacion 100: "+token+" -> Palabra reservada");
        break;
        case(101):
            ui->textEdit_2->append("Estado de aceptacion 101: "+token+" -> Identificador");
        break;
        case(102):
            ui->textEdit_2->append("Estado de aceptacion 102: "+token+" -> Entero");
        break;
        case(103):
            ui->textEdit_2->append("Estado de aceptacion 103: "+token+" -> Real");
        break;
        case(104):
            ui->textEdit_2->append("Estado de aceptacion 104: "+token+" -> N.Cientifica");
        break;
        case(105):
            ui->textEdit_2->append("Estado de aceptacion 105: "+token+" -> Suma");
        break;
        case(106):
            ui->textEdit_2->append("Estado de aceptacion 106: "+token+" -> Resta");
        break;
        case(107):
            ui->textEdit_2->append("Estado de aceptacion 107: "+token+" -> Multiplicacion");
        break;
        case(108):
            ui->textEdit_2->append("Estado de aceptacion 108: "+token+" -> Division");
        break;
        case(109):
            ui->textEdit_2->append("Estado de aceptacion 109: "+token+" -> Asignacion");
        break;
        case(110):
            ui->textEdit_2->append("Estado de aceptacion 110: "+token+" -> Igual que");
        break;
        case(111):
            ui->textEdit_2->append("Estado de aceptacion 111: "+token+" -> Menor que");
        break;
        case(112):
            ui->textEdit_2->append("Estado de aceptacion 112: "+token+" -> Menor o igual que");
        break;
        case(113):
            ui->textEdit_2->append("Estado de aceptacion 113: "+token+" -> Mayor");
        break;
        case(114):
            ui->textEdit_2->append("Estado de aceptacion 114: "+token+" -> Mayor o igual que");
        break;
        case(115):
            ui->textEdit_2->append("Estado de aceptacion 115: "+token+" -> Diferente que");
        break;
        case(116):
            ui->textEdit_2->append("Estado de aceptacion 116: "+token+" -> Negacion Logica NOT");
        break;
        case(117):
            ui->textEdit_2->append("Estado de aceptacion 117: "+token+" -> Y Logico AND");
        break;
        case(118):
            ui->textEdit_2->append("Estado de aceptacion 118: "+token+" -> O Logico OR");
        break;
        case(119):
            ui->textEdit_2->append("Estado de aceptacion 119: "+token+" -> Parentesis que abre");
        break;
        case(120):
            ui->textEdit_2->append("Estado de aceptacion 120: "+token+" -> Parentesis que cierra");
        break;
        case(121):
            ui->textEdit_2->append("Estado de aceptacion 121: "+token+" -> Corchete que abre");
        break;
        case(122):
            ui->textEdit_2->append("Estado de aceptacion 122: "+token+" -> Corchete que cierra");
        break;
        case(123):
            ui->textEdit_2->append("Estado de aceptacion 123: "+token+" -> Punto y coma");
        break;
        case(124):
            ui->textEdit_2->append("Estado de aceptacion 124: "+token+" -> Coma");
        break;
        case(125):
            ui->textEdit_2->append("Estado de aceptacion 125: "+token+" -> Caracter");
        break;
        case(126):
            ui->textEdit_2->append("Estado de aceptacion 126: "+token+" -> Cadena");
        break;
        case(127):
            ui->textEdit_2->append("Estado de aceptacion 127: "+token+" -> Comentario de linea");
        break;
        case(128):
            ui->textEdit_2->append("Estado de aceptacion 128: "+token+" -> Modulo");
        break;
        case(129):
            ui->textEdit_2->append("Estado de aceptacion 129: "+token+" -> Incremento");
        break;
        case(130):
            ui->textEdit_2->append("Estado de aceptacion 130: "+token+" -> Decremento");
        break;
        case(131):
            ui->textEdit_2->append("Estado de aceptacion 131: "+token+" -> Potencia");
        break;
        case(132):
            ui->textEdit_2->append("Estado de aceptacion 132: "+token+" -> Suma y asignacion");
        break;
        case(133):
            ui->textEdit_2->append("Estado de aceptacion 133: "+token+" -> Resta y asignacion");
        break;
        case(134):
            ui->textEdit_2->append("Estado de aceptacion 134: "+token+" -> Multiplicacion y asignacion");
        break;
        case(135):
            ui->textEdit_2->append("Estado de aceptacion 135: "+token+" -> Division y asignacion");
        break;
        case(136):
            ui->textEdit_2->append("Estado de aceptacion 136: "+token+" -> Modulo y asignacion");
        break;
        case(137):
            ui->textEdit_2->append("Estado de aceptacion 137: "+token+" -> Comentario de bloque");
        break;
        case(138):
            ui->textEdit_2->append("Estado de aceptacion 138: "+token+" -> Doble punto");
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
    else if (state == 503)
        ui->textEdit_3->setText("Error con estado: "+QString::number(state)+" Operador AND incompleto");
    else if (state == 504)
        ui->textEdit_3->setText("Error con estado: "+QString::number(state)+" Operador OR incompleto");
    else if (state == 505)
        ui->textEdit_3->setText("Error con estado: "+QString::number(state)+" Caracter vacio");
    else if (state == 506)
        ui->textEdit_3->setText("Error con estado: "+QString::number(state)+" Inicio invalido de token");
    else if (state == 507)
        ui->textEdit_3->setText("Error con estado: "+QString::number(state)+" Caracter debe terminar en caracter ' y tener longitud de 1 caracter");
    else if (state == 508)
        ui->textEdit_3->setText("Error con estado: "+QString::number(state)+" Identificador no puede terminar en '_'");
    else if (state == 509)
        ui->textEdit_3->setText("Error con estado: "+QString::number(state)+" Comentario de bloque /* sin terminar");
    else if (state == 510)
        ui->textEdit_3->setText("Error con estado: "+QString::number(state)+" String sin terminar");
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
    for (int i = 0; i < sourceText.size(); i++ ) {
        qInfo() << "Estado actual: " << state;
        if (state < 100)
            state = states[state][relacionar(sourceText[i])];
        qInfo() << "Link:" << relacionar(sourceText[i]);
        qInfo() << "Token actual: " << token;
        qInfo() << "Simbolo actual: " << sourceText[i] << (int)sourceText[i].unicode();
        qInfo() << "Estado resultante:" << state << "\n";
        if (state == 0)
            continue;
        else if (state < 100){
            token.append(sourceText[i]);
        }
        if (state >= 100 && state < 500){
            if (state == 100 && !(std::find(std::begin(reservedWords), std::end(reservedWords), token) != std::end(reservedWords))){
                state = 101;
            } else if (std::find(std::begin(autoConclusiveStates), std::end(autoConclusiveStates), state) != std::end(autoConclusiveStates)){
                token.append(sourceText[i]);
                appendToken(state, token);
                token = "";
                state = 0;
                continue;
            }
            appendToken(state, token);
            // Set current char as the start of a new token if this was the cause of a final state
            if (relacionar(sourceText[i]) < 27){
                token = sourceText[i];
                state = states[0][relacionar(sourceText[i])];
            }
            else {
                token = "";
                state = 0;
            }
        } else if(state >= 500) {
            errorToken(state);
            return;
        }
    }
    // EOT
    if (!token.isEmpty()) {
        if (state < 100){
            state = states[state][relacionar(QChar(10))];
            if (state == 16)
                state = 507;
            else if ((state == 17) && (token.size()==1 || !token.endsWith('\"')))
                state = 510;
            else if (state == 26 || state == 27 )
                state = 509;
        }
        qInfo() << "Simbolo actual: EOT" << (int)QChar(10).unicode();
        qInfo() << "Estado final:" << state;
        if (state >= 100 && state < 500){
            if (state == 100 && !(std::find(std::begin(reservedWords), std::end(reservedWords), token) != std::end(reservedWords))){
                state = 101;
            }
            appendToken(state, token);
        } else if(state >= 500) {
            errorToken(state);
        }
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Guardar archivo","", tr("Archivo Spes (*.spes)"));
    if (fileName.isEmpty()) {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QMessageBox::warning(this, "No se pudo abrir el archivo ", file.errorString());
        return;
    }
    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();
}

