//Socket.h
#pragma once
#include <iostream>
#include <fstream>
#include "WinSock2.h"

using namespace std;

const int STRLEN = 256;

class Socket
{
    protected:
        WSADATA wsaData;
        SOCKET mySocket;
        SOCKET myBackup;
        SOCKET acceptSocket;
        sockaddr_in myAddress;
        int count;
    public:
        Socket();
        ~Socket();
        bool SendData( char* );
        bool RecvData( char*, int );
        void CloseConnection();
        void GetAndSendMessage();
};













