//Socket.h

//Now go to Project -> Build Options -> Linker settings
//(make sure the project is selected on the left, not a build target)
//and add in the left list the library "ws2_32" (not a path!).

#pragma once
#include <iostream>
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












