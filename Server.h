/**
 * @file Server.h
 * @author Johnny Aguero
 * @brief Create the Server socket and the necessary logic
 * @version 0.1
 * @date 2021-05-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <map>

/**
 * @brief Create the socket server and de logic of the send a receive menssage
 *  
 * @param port, port of the server.
 */
class Server{
    public:
        int bufsize = 1024;
        char buffer[1024];
        int client, server;
        //Json::Reader reader;
        //Json::Value dataS;
        //Json::StyledWriter writer;

    //Constructor
    Server(int port){
        struct sockaddr_in server_addr;
        socklen_t size;

        client = socket(AF_INET, SOCK_STREAM, 0);
        if (client < 0) {
            std::cout << "\nError estableciendo el socket" << std::endl;
            exit(1);
        }
        std::cout << "\n=> Socket server creado..." << std::endl;

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        server_addr.sin_port = htons(port);


        if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0) 
        {
            std::cout << "=> Error estableciendo conexion" << std::endl;
            exit(1);
        }

        size = sizeof(server_addr);
        std::cout << "=> Buscando clientes" << std::endl;

        listen(client, 1);

        int clientCount = 1;
        server = accept(client,(struct sockaddr *)&server_addr,&size);

        if (server < 0) 
            std::cout << "=> Error aceptando el cliente" << std::endl;

        std::cout << "=> Conectado con el cliente #" << clientCount << std::endl;
        strcpy(buffer, "=> Server connected...\n");
        send(server, buffer, bufsize, 0);

    }

    //Metodos
    std::string Recibir();
    void Enviar(std::string);

};

/**
 * @brief Receive the menssage of the client socket
 *  
 * @return text that receive
 */
std::string Server::Recibir(){
    int bufsizeR = 1024;
    char bufferR[1024];
    recv(server, bufferR, bufsizeR, 0);
    std::string text = bufferR;
    return text;
}

/**
 * @brief Send the menssage for the socket server.
 *  
 * @param text, text of the send menssage
 */
void Server::Enviar(std::string text){
    int bufsizeS = 1024;
    char bufferS[1024];
    std::copy(text.begin(), text.end(), bufferS);
    send(server, bufferS, bufsizeS, 0);
}

#endif 
