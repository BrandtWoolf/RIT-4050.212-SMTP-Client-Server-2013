//ServerSocket
#include "ServerSocket.h"
#include <dirent.h>
#include <sstream>

void ServerSocket::StartHosting( int port )
{
     Bind( port );
     Listen();
}

void ServerSocket::Listen()
{
    //cout<<"LISTEN FOR CLIENT..."<<endl;

    if ( listen ( mySocket, 1 ) == SOCKET_ERROR )
    {
        cerr<<"ServerSocket: Error listening on socket\n";
        system("pause");
        WSACleanup();
        exit(15);
    }

    //cout<<"ACCEPT CONNECTION..."<<endl;

    acceptSocket = accept( myBackup, NULL, NULL );
    while ( acceptSocket == SOCKET_ERROR )
    {
        acceptSocket = accept( myBackup, NULL, NULL );
    }
    mySocket = acceptSocket;
}

void ServerSocket::Bind( int port )
{
    myAddress.sin_family = AF_INET;
    myAddress.sin_addr.s_addr = inet_addr( "0.0.0.0" );
    myAddress.sin_port = htons( port );

    //cout<<"BIND TO PORT "<<port<<endl;

    if ( bind ( mySocket, (SOCKADDR*) &myAddress, sizeof( myAddress) ) == SOCKET_ERROR )
    {
        cerr<<"ServerSocket: Failed to connect\n";
        system("pause");
        WSACleanup();
        exit(14);
    }
}

bool ServerSocket::listFile(){

    if (fileNames.size() > 0)
        fileNames.clear();

    ifstream inn;
    string   str = "test";
    DIR *pDIR;
    struct dirent *entry;
    if( pDIR=opendir("./") ){
        while(entry = readdir(pDIR)){
            if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
                fileNames.push_back(entry->d_name);
            }
        }
    }
    closedir(pDIR);
    if (fileNames.size() == 0)
        return false;
    if (fileNames.size() > 0)
        return true;
}

string ServerSocket::convertInt(int number){
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}


