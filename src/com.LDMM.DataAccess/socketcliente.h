/*
 * socketcliente.h
 *
 *  Created on: Feb 27, 2015
 *      Author: fabian
 */

#ifndef SOURCES_SOCKETCLIENTE_H_
#define SOURCES_SOCKETCLIENTE_H_
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

class SocketCliente{
public:
    SocketCliente();
    bool connect(const char* targetIP,int targetPORT);
    void sendMessage(const char *msn);
private:
    int descriptor;
    sockaddr_in info;
    static void * controlador(void *obj);
};

#endif /* SOURCES_SOCKETCLIENTE_H_ */
