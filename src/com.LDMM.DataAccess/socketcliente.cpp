/*
 * socketcliente.cpp
 *
 *  Created on: Feb 27, 2015
 *      Author: fabian
 */

#include "socketcliente.h"
#include "pthread.h"
#include <string>

SocketCliente::SocketCliente(){
	descriptor = 0;
}

bool SocketCliente::connect(const char* targetIP,int targetPORT)
{
    descriptor = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(descriptor < 0)
        return false;
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = inet_addr(targetIP);
    info.sin_port = ntohs(targetPORT);
    //info.sin_addr.s_addr = inet_addr("192.168.1.108");
    //info.sin_port = ntohs(7070);
    memset(&info.sin_zero,0,sizeof(info.sin_zero));

    if((::connect(descriptor,(sockaddr*)&info,(socklen_t)sizeof(info))) < 0)
     return false;

    pthread_t hilo;
    pthread_create(&hilo,0,SocketCliente::controlador,(void *)this);
    pthread_detach(hilo);
    return true;
}


void * SocketCliente::controlador(void *obj)
{
    SocketCliente *padre = (SocketCliente*)obj;

    while (true) {
        string mensaje;
        while (1) {
            char buffer[10] = {0};
            int bytes = recv(padre->descriptor,buffer,10,0);
            mensaje.append(buffer,bytes);
            if(bytes <= 0)
            {
                close(padre->descriptor);
                pthread_exit(NULL);
            }
            if(bytes < 10)
                break;
        }
    }
    close(padre->descriptor);
    pthread_exit(NULL);
}


void SocketCliente::sendMessage(const char *msn){
	send(descriptor,msn,strlen(msn),0);
	//cout << "bytes enviados "<< send(descriptor,msn,strlen(msn),0) << endl;
}
