//Main.cpp
//In Dev-C++ you must add the libws2_32.a library to
//   Project-->Project Options-->Parameters--Linker-->Add Library or Object
// libws2_32 is in the Dev-C++/lib folder
#include <iostream>
#include <windows.h>
#include <string>
#include "Socket.h"
#include "ServerSocket.h"

using namespace std;

void validateCommand(char[], int&);

int main()
{
    int port = 8888;

    string ipAddress;
    string password = "1234";
    char recMessage[STRLEN];

    ServerSocket sockServer;

    //SERVER
    cout<<".....SERVER STARTUP....."<< endl << "REQUESTING LOGIN INFO....";
    sockServer.StartHosting( port );

    //send credential request to client
    char message[28] = "Please enter credentials: ";
    sockServer.SendData(message);

    //recieve password from client
    sockServer.RecvData(recMessage, STRLEN);

    string temp = recMessage;

    //disconnect if incorrect
    if (temp != password)
    {
        char message[44] = "\t***INVALID CREDENTIALS****\nDISCONNECTING";
        sockServer.SendData(message);
        sockServer.CloseConnection();
        system("pause");
        return 0;
    }

    if (temp == password)
    {
        char message[19] = "\tLOGIN SUCCESSFUL";
        sockServer.SendData(message);
    }

    while (true)
    {
        char message2 [28] = "OPTIONS: List, Send, Quit: ";
        sockServer.SendData(message2);

        sockServer.RecvData(recMessage, STRLEN);

        int check = -1;
        validateCommand(recMessage, check);

        //valid command for List
        if(check == 1){
            char message6 [5] = "List";
            sockServer.SendData(message6);

            if (!(sockServer.listFile())){
                char message5 [25] = "***No files in directory";
                sockServer.SendData(message5);
            }
            else{
                string fileNumTemp = sockServer.convertInt(sockServer.fileNames.size());
                char *fileNum = new char [fileNumTemp.length() + 1];
                strcpy(fileNum,fileNumTemp.c_str());
                sockServer.SendData(fileNum);

                cout << endl;

                for (int i = 0; i < sockServer.fileNames.size(); i++)
                {
                    string fileName = sockServer.fileNames.at(i);
                    char *fileMessage = new char [fileName.length() + 1];
                    strcpy(fileMessage,fileName.c_str());
                    sockServer.SendData(fileMessage);
                    Sleep (50);
                }
            }
        }

        //valid command for Send
        else if(check == 2){
            char open[5] = "send";
            string fileTxt;

            sockServer.SendData(open);
            sockServer.RecvData(recMessage, STRLEN);
            //cout << recMessage << endl;
            ifstream fin;
            fin.open(recMessage);
            if(!fin.is_open()){
                char fail[5] = "fail";
                sockServer.SendData(fail);
            }

            else{
                char okay[5] ="okay";
                sockServer.SendData(okay);
                string fileText;
                do{
                    getline(fin, fileText);
                    char *s1 = new char[fileText.length()+1];
                    strcpy(s1, fileText.c_str());
                    sockServer.SendData(s1);
                    //getline(fin, fileText);
                    Sleep (500);
                    if (fin.eof())
                    {
                        char stopBit[19] = "EOFEOFEOFEOFEOFEOF";
                        sockServer.SendData(stopBit);
                    }
                }while(!fin.eof());
                fin.close();
            }
        }
        //valid command for Quit
        else if(check == 3){
            char message4 [8] = "Goodbye";
            sockServer.SendData(message4);
            sockServer.CloseConnection();
            cout << endl << "\t***DISCONNECTED" << endl;
            system("pause");
            return 0;
        }

        else{
            char message3 [14] = "INVALID ENTRY";
            sockServer.SendData(message3);
        }
    }
    system("pause");

    return 0;
}

void validateCommand(char recMessage[], int &check){
    string command(recMessage);
    if(command == "List" || command == "list" || command == "LIST")
        check = 1;
    else if(command == "Send" || command == "send" || command == "SEND")
        check = 2;
    else if(command == "Quit" || command == "quit" || command == "QUIT")
        check = 3;
    else
        check = -1;
}












