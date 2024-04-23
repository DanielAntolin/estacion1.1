#include "controlador.h"
Controlador::Controlador() {
    // struch hexadecimal
     HexMessage mensaje;
     BinMessage mensajeBinario;

     // Configuración de la dirección del servidor
     direccionServidor.sin_family = AF_INET;
     direccionServidor.sin_port = htons(8080);
     inet_pton(AF_INET,"127.0.0.1", &direccionServidor.sin_addr.s_addr);// Cambiar a la dirección IP del servidor
     // configuracion de la direccion del servidor
     direccionCliente.sin_family = AF_INET;
     direccionCliente.sin_addr.s_addr = INADDR_ANY;
     direccionCliente.sin_port = htons(8083);

}
Controlador::~Controlador() {
    // Cerrar todos los sockets
    for (int i = 0; i < 3; ++i) {
        close(enviarSocket[i]);
        close(recibirSocket[i]);
    }
}
void Controlador::inicializarEnvio(int puerto, int index) {
    // Crear socket para enviar
    enviarSocket[index] = socket(AF_INET, SOCK_DGRAM, 0);
    enviarPuertos[index] = puerto;
}
void Controlador::inicializarRecepcion(int puerto, int index) {
    // Crear socket para recibir
    recibirSocket[index] = socket(AF_INET, SOCK_DGRAM, 0);

    // Enlazar el socket a un puerto específico
    sockaddr_in direccionEscucha = direccionCliente;

    switch (index) {
    case INDEX_STRING:
        direccionEscucha.sin_port = htons(8083);
        break;
    case INDEX_HEXADECIMAL:
        direccionEscucha.sin_port = htons(PUERTO_REC_HEXADECIMAL);
        break;
    case INDEX_BINARIO:
        direccionEscucha.sin_port = htons(PUERTO_REC_BINARIO);
        break;
    default:
        break;
    }
    if(bind(recibirSocket[index], reinterpret_cast<sockaddr*>(&direccionEscucha), sizeof(direccionEscucha))<=0){
        std::cout << "Info: "<< strerror(errno) << std::endl;
    }

    recibirPuertos[index] = puerto;

    // Iniciar un hilo para la recepción de mensajes en este puerto
    std::thread receptor(&Controlador::recibirMensajes, this, index,direccionEscucha);
    receptor.detach(); // Liberar el hilo principal del control del hilo de recepción
}
void Controlador::recibirMensajes(int index,sockaddr_in direccion) {

    while (true) {
        char buffer[1024];
        std::cout<<"Estoy aqui 1"<<std::endl;
        socklen_t len = sizeof(direccion);
        recvfrom(recibirSocket[index], buffer, sizeof(buffer), 0, reinterpret_cast<sockaddr*>(&direccion), &len);
        std::string mensaje(buffer);
        std::cout<<"Estoy aqui 2"<<std::endl;
        std::cout << "Puerto " << recibirPuertos[index] << " - Mensaje recibido: " << mensaje << std::endl;
        std::cout<<"Estoy aqui 3"<<std::endl;
        std::vector<unsigned char> bytes;
        std::cout<<"Estoy aqui 3"<<std::endl;
        for (size_t i = 0; i < mensaje.size(); i += 2) {
            unsigned char byte = std::stoi(mensaje.substr(i, 2), nullptr, 16);
            bytes.push_back(byte);
        }
        std::cout<<"Estoy aqui 4"<<std::endl;
        mostarVector(bytes);
        switch (index) {
        case INDEX_STRING:
            // VERIFICAR STRING
            break;
        case INDEX_HEXADECIMAL:
            if(validad_respuestaHexa(bytes)){
              // todo bien
        }
            else{


            }
        break;
        case INDEX_BINARIO:
            // VERIFICAR BINARIO
            break;
        }


    }

}
void Controlador:: mostarVector(std::vector<unsigned char> vector){
    std::cout<< "Mostrando vector que ha recibido"<<std::endl;
    for (int i = 0; i < vector.size(); i++) {
        int d = vector[i];
        std::cout <<" |"<< std::hex << d;
    }
    std::cout<<std::endl;
}
void Controlador::enviarMensaje(std::vector <unsigned char>array, int index) {
    // Enviar el mensaje al servidor
    sockaddr_in direccionDestino = direccionServidor;
    switch (index) {
    case INDEX_STRING:
        direccionDestino.sin_port = htons(PUERTO_ENV_STRING);
        break;
    case INDEX_HEXADECIMAL:
        direccionDestino.sin_port = htons(PUERTO_ENV_HEXADECIMAL);
        break;
    case INDEX_BINARIO:
        direccionDestino.sin_port = htons(PUERTO_ENV_BINARIO);
        break;
    default:
        break;
    }

    sendto(enviarSocket[index], array.data(), array.size(), 0, reinterpret_cast<sockaddr*>(&direccionDestino), sizeof(direccionDestino));

}


std::vector<unsigned char> HexMessage::generar_mensajeHexa() const {
    std::vector<unsigned char> mensaje;

    unsigned char cabecera1 = (cabecera >> 8) & 0xFF;
    unsigned char cabecera2 = cabecera & 0xFF;

    mensaje.push_back(cabecera1);
    mensaje.push_back(cabecera2);
    mensaje.push_back(destino);

    unsigned char comando1 = (comando >> 8) & 0xFF;
    unsigned char comando2 = comando & 0xFF;
    mensaje.push_back(comando1);
    mensaje.push_back(comando2);
    mensaje.push_back(argumento1);
    if(comando == MOVIENTO){
        mensaje.push_back(argumento2);
    }
    std::cout<<" Genera el mensaje:"<<std::endl;
    for (int i = 0; i < mensaje.size(); i++) {
        int d = mensaje[i];
        std::cout <<" | " <<std::hex << d;
    }
    std::cout<<std::endl;


    return mensaje;
}
std::vector<unsigned char> BinMessage::generar_mensajeBin() const {
    std::vector<unsigned char> mensaje;
    //std::cout<<"Pruebas: "<< CABECERA_BIN << ALUMNO_DEST_BIN << ZOOM << ZOOM_AUM<< FINAL_BIN<<std::endl;
    mensaje.push_back(cabecera);
    mensaje.push_back(destinatario);
    mensaje.push_back(comando);
    mensaje.push_back(argumento);
    mensaje.push_back(final);


    return mensaje;
}


bool Controlador::validad_respuestaHexa(std::vector<unsigned char> array){
    unsigned char cabecera1 = array[0];
    unsigned char cabecer2 = array[1];
    int16_t resultado = (cabecera1 << 8) | cabecer2;

    if(resultado != CABECERA){
        std::cout<< "error 1 ";
        return false;
    }
    unsigned char destinatario = array[2];
    std::cout<< destinatario<< " espacio "<<array[2]<<std::endl;
    if(destinatario != ESTACION_DEST){
        std::cout<< "error 2";
        return false;
    }
    unsigned char comando1 = array[3];
    unsigned char comando2 = array[4];
    int16_t comandoRecibido = (comando1 << 8) | comando2;

    unsigned char respuesta = array[5];
    if(respuesta != RES_OK){
        std::cout<< "error 4 ";
        return false;
    }

    return true;
}



