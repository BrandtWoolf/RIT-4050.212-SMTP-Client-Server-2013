//Main.cpp
//In Dev-C++ you must add the libws2_32.a library to
//   Project-->Project Options-->Parameters--Linker-->Add Library or Object
// libws2_32 is in the Dev-C++/lib folder
#include <iostream>
#include <fstream>
#include "Socket.h"
#include "ClientSocket.h"

using namespace std;

int main()
{
    int port = 8888;
    string ipAddress;
    char recMessage[STRLEN];

    //Client
    cout<<"Enter an IP address of server: ";
    cin>>ipAddress;

    ClientSocket sockClient;

    //connect to server
    cout<<"ATTEMPTING TO CONNECT..."<<endl << endl;
    sockClient.ConnectToServer( ipAddress.c_str(), port );

    //Recieve message from server (authentication request)
    sockClient.RecvData( recMessage, STRLEN );
    cout << recMessage;

    //send request to server (password)
    sockClient.GetAndSendMessage();

    //server response (valid or invalid password)
    sockClient.RecvData( recMessage, STRLEN );
    cout << recMessage << endl;

    string temp = recMessage;

    if (temp == "\t***INVALID CREDENTIALS****\nDISCONNECTING")
    {
        sockClient.CloseConnection();
        system("pause");
        return 0;
    }

    while (true)
    {
        //server list of actions to take
        sockClient.RecvData( recMessage, STRLEN );
        cout << recMessage;

        //client response of action
        sockClient.GetAndSendMessage();

        //server responds to selected action
        sockClient.RecvData( recMessage, STRLEN );

        //if quit is entered, server sends "Goodbye"
        string temp = recMessage;
        if (temp == "INVALID ENTRY")
        {
            cout << recMessage << endl;
        }
        else if (temp == "Goodbye")
        {
            sockClient.CloseConnection();
            cout << endl << "\t***DISCONNECTED" << endl;
            system("pause");
            return 0;
        }
        else if (temp == "List")
        {
            sockClient.RecvData( recMessage, STRLEN );
            temp = recMessage;
            if (temp != "***No files in directory"){
                int num = atoi(recMessage);
                for (int i = 0; i < num; i++)
                {
                    sockClient.RecvData( recMessage, STRLEN );
                    cout << endl <<"\t" << recMessage;
                }
                cout << endl << endl;
            }
        }

        else if(temp == "send")
        {
            cout << "Enter file name: ";
            string fileName;
            cin >> fileName;

            char *cfilename = new char[fileName.length()+1];
            strcpy(cfilename,fileName.c_str());
            sockClient.SendData(cfilename);

            sockClient.RecvData(recMessage, STRLEN);
            temp = recMessage;
            if(temp == "fail"){
                cerr << "\tFile does not exist" << endl;
            }
            else if(temp == "okay"){
                ofstream fout;
                fout.open(fileName.c_str());
                sockClient.RecvData(recMessage, STRLEN);
                //cout << "..." << recMessage << endl;
                string txt(recMessage);
                while(txt != "EOFEOFEOFEOFEOFEOF"){
                    fout << txt << endl;
                    sockClient.RecvData(recMessage, STRLEN);
                    txt = recMessage;
                }
                fout.close();
            }
        }
    }

    system("pause");

    return 0;
}











