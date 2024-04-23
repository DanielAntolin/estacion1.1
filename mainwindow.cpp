#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(Controlador& controlador,QWidget *parent)
    : QMainWindow(parent),
    controlador(controlador),
     ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    // inicialzar envios
    controlador.inicializarEnvio(PUERTO_ENV_STRING, INDEX_STRING);
    controlador.inicializarEnvio(PUERTO_ENV_HEXADECIMAL, INDEX_HEXADECIMAL);
    controlador.inicializarEnvio(PUERTO_ENV_BINARIO, INDEX_BINARIO);
    // inicializar recepcion
    controlador.inicializarRecepcion(8083,INDEX_STRING);
    // inicializarRecepcion(PUERTO_REC_HEXADECIMAL,INDEX_HEXADECIMAL);
    // inicializarRecepcion(PUERTO_REC_BINARIO,INDEX_BINARIO);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btMoviento_clicked()
{
    HexMessage mensaje;
    mensaje.cabecera = CABECERA;
    mensaje.destino = ESTACION_DEST;
    mensaje.comando = HABILITAR_MOVIMIENTO;
    mensaje.argumento1 = HABILTAR;
    std::vector<unsigned char> mensajeHabiltar = mensaje.generar_mensajeHexa();
    QString textoCabecera = QString::number(mensaje.cabecera);

    controlador.enviarMensaje(mensajeHabiltar,INDEX_STRING);
    // Establecer el texto del widget
    ui->textoUsuario->setText(textoCabecera);
}


void MainWindow::on_btMoviento_2_clicked()
{
    HexMessage mensaje;
    mensaje.cabecera = CABECERA;
    mensaje.destino = ESTACION_DEST;
    mensaje.comando = HABILITAR_MOVIMIENTO;
    mensaje.argumento1 = DESHABILITAR;
    std::vector<unsigned char> mensajeHabiltar = mensaje.generar_mensajeHexa();
    controlador.enviarMensaje(mensajeHabiltar,INDEX_STRING);
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    HexMessage mensaje;
    mensaje.cabecera = CABECERA;
    mensaje.destino = ESTACION_DEST;
    mensaje.comando = MOVIENTO;
    switch (value) {
    case 0:
        mensaje.argumento1 = MAX_VELOCIDAD_IZQUIERDA;
        break;
    case 1:
        mensaje.argumento1 = PARAR_EJE_X;
        break;
    case 2:
        mensaje.argumento1 = MAX_VELOCIDAD_DERECHA;
        break;
    }
    int slider2 =0 ;
    slider2 = ui->verticalSlider->value();
    switch (slider2) {
    case 0:
        mensaje.argumento2 = MAX_VELOCIDAD_ABAJO;
        break;
    case 1:
        mensaje.argumento2 = PARAR_EJE_Y;
        break;
    case 2:
        mensaje.argumento2 = MAX_VELOCIDAD_ARRIBA;
        break;
    }
    std::vector<unsigned char> mensajeMoviento = mensaje.generar_mensajeHexa();
    controlador.enviarMensaje(mensajeMoviento,INDEX_STRING);
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    HexMessage mensaje;
    mensaje.cabecera = CABECERA;
    mensaje.destino = ESTACION_DEST;
    mensaje.comando = MOVIENTO;
    switch (value) {
    case 0:
        mensaje.argumento2 = MAX_VELOCIDAD_ABAJO;
        break;
    case 1:
        mensaje.argumento2 = PARAR_EJE_Y;
        break;
    case 2:
        mensaje.argumento2 = MAX_VELOCIDAD_ARRIBA;
        break;
    }
    int slider2 =0 ;
    slider2 = ui->verticalSlider->value();
    switch (slider2) {
    case 0:
        mensaje.argumento1 = MAX_VELOCIDAD_IZQUIERDA;
        break;
    case 1:
        mensaje.argumento1 = PARAR_EJE_X;
        break;
    case 2:
        mensaje.argumento1 = MAX_VELOCIDAD_DERECHA;
        break;
    }
    std::vector<unsigned char> mensajeMoviento = mensaje.generar_mensajeHexa();
    controlador.enviarMensaje(mensajeMoviento,INDEX_STRING);
}


void MainWindow::on_btZoomMas_clicked()
{
    BinMessage mensaje;
    mensaje.cabecera = CABECERA_BIN;
    mensaje.destinatario = ALUMNO_DEST_BIN;
    mensaje.comando = ZOOM;
    mensaje.argumento = ZOOM_MAS;
    std::vector<unsigned char> array = mensaje.generar_mensajeBin();
    controlador.enviarMensaje(array,INDEX_STRING);
}


void MainWindow::on_btZoomMenos_clicked()
{
    BinMessage mensaje;
    mensaje.cabecera = CABECERA_BIN;
    mensaje.destinatario = ALUMNO_DEST_BIN;
    mensaje.comando = ZOOM;
    mensaje.argumento = ZOOM_MENOS;
    std::vector<unsigned char> array = mensaje.generar_mensajeBin();
    controlador.enviarMensaje(array,INDEX_STRING);
}


void MainWindow::on_btCamaraDia_clicked()
{
    BinMessage mensaje;
    mensaje.cabecera = CABECERA_BIN;
    mensaje.destinatario = ALUMNO_DEST_BIN;
    mensaje.comando = CAMBIO_CAMARA;
    mensaje.argumento = DIA;
    std::vector<unsigned char> array = mensaje.generar_mensajeBin();
    controlador.enviarMensaje(array,INDEX_STRING);
}


void MainWindow::on_btCamaraTermica_clicked()
{
    BinMessage mensaje;
    mensaje.cabecera = CABECERA_BIN;
    mensaje.destinatario = ALUMNO_DEST_BIN;
    mensaje.comando = CAMBIO_CAMARA;
    mensaje.argumento = TERMICA;
    std::vector<unsigned char> array = mensaje.generar_mensajeBin();
    controlador.enviarMensaje(array,INDEX_STRING);
}

