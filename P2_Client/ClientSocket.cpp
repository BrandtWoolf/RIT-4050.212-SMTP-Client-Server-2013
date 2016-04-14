//ClientSocket
#include "ClientSocket.h"

void ClientSocket::ConnectToServer( const char *ipAddress, int port )
{
    myAddress.sin_family = AF_INET;
    myAddress.sin_addr.s_addr = inet_addr( ipAddress );
    myAddress.sin_port =  htons(port);

    //cout<<"CONNECTED"<<endl;

    if ( connect( mySocket, (SOCKADDR*) &myAddress, sizeof( myAddress ) ) == SOCKET_ERROR )
    {
        cerr<<"ClientSocket: Failed to connect\n";
        system("pause");
        WSACleanup();
        exit(13);
    }
}
