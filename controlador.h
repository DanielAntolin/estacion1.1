#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include <vector>
#include <iostream>
#include <iomanip>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <errno.h>
#include <cstring>

// -- CONSTANTES BINARIO
// constantes especiales
const uint16_t CABECERA_BIN = 0b110100;
const uint16_t FINAL_BIN = 0b1011;

 // Destinatarios binarios
const uint8_t ALUMNO_DEST_BIN = 0b01;
const uint8_t ESTACION_DEST_BIN = 0b10;

 // Comandos binarios
const uint8_t ZOOM = 0b01;
const uint8_t CAMBIO_CAMARA = 0b00;

// ARGUMENTO ZOOM
const uint8_t  ZOOM_MAS = 0b00;
const uint8_t  ZOOM_MENOS = 0b01;

// ARGUMENTO CAMARA
const uint8_t DIA = 0b00;
const uint8_t TERMICA = 0b10;

// Respuestas binario

 const uint16_t RES_OK_BIN = 0b01000000;
 const uint16_t RES_NOK_BIN = 0b00001000;

 struct BinMessage
 {
     uint16_t cabecera;
     uint8_t destinatario;
     uint8_t comando;
     uint8_t argumento;
     uint16_t final;
     std::vector<unsigned char> generar_mensajeBin() const;
 };

// -- CONSTANTES HEXADECIMAL
// Constantes para caracteres especiales
static const int16_t CABECERA = 0x71A2;
// Destinatarios
const unsigned char ALUMNO_DEST = 0x09;
const unsigned char ESTACION_DEST = 0xFA;

// Comandos
const int16_t HABILITAR_MOVIMIENTO = 0xFA01;
const int16_t MOVIENTO = 0x0C02;

// Argumentos HABILITAR MOVIENTO
const char SIN_ARGUMENTO = 0XD9;
const char DESHABILITAR = 0x00;
const char HABILTAR= 0xFF;

// ARGUMNETOS MOVIENTO
const char MAX_VELOCIDAD_DERECHA = 0xD2;
const char MAX_VELOCIDAD_IZQUIERDA = 0xC9;
const char PARAR_EJE_X = 0x65;
const char MAX_VELOCIDAD_ARRIBA = 0x61;
const char MAX_VELOCIDAD_ABAJO = 0x00;
const char PARAR_EJE_Y = 0x31;
// Reespuesta HEXADECIMAL
const unsigned char RES_OK = 0xF4;
const unsigned char RES_NOK = 0xFA;
struct HexMessage {
    int16_t cabecera;
    unsigned char destino;
    int16_t comando;
    unsigned char argumento1;
    unsigned char argumento2;
    std::vector<unsigned char> generar_mensajeHexa() const;
};
// -- UDP
// PUERTOS ENVIOS
const uint16_t PUERTO_ENV_STRING = 8080;
const int PUERTO_ENV_HEXADECIMAL = 8081;
const int PUERTO_ENV_BINARIO = 8082;

// PUERTOS ESCUCHA
const uint16_t PUERTO_REC_STRING = 8083;
const int PUERTO_REC_HEXADECIMAL = 8084;
const int PUERTO_REC_BINARIO = 8085;

// INDEX PUERTOS
const int INDEX_STRING = 0;
const int INDEX_HEXADECIMAL = 1;
const int INDEX_BINARIO = 2;
class Controlador
{
private:
    int enviarSocket[3];
    int recibirSocket[3];
    int enviarPuertos[3];
    int recibirPuertos[3];
    sockaddr_in direccionServidor;
    sockaddr_in direccionCliente;

public:
    Controlador();
    ~Controlador();
    bool validad_respuestaHexa(std::vector<unsigned char> array);
    bool validar_respuestaBin(std::vector<unsigned char> array);
    void inicializarEnvio(int puerto, int index);
    void inicializarRecepcion(int puerto, int index);
    void recibirMensajes(int index,sockaddr_in direccion);
    void enviarMensaje(std::vector<unsigned char> array, int index);
    std::vector<unsigned char> vectorHexa;
    void mostarVector(std::vector<unsigned char> vector);
    std::string decimalToBinary(int decimal);
};

#endif // CONTROLADOR_H
