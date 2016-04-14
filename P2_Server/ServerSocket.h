//Server Socket
#include "Socket.h"
#include <vector>

class ServerSocket : public Socket
{
    public:
        vector<string> fileNames;
    public:
        void Listen();
        void Bind( int port );
        void StartHosting( int port );
        bool listFile();
        string convertInt(int);
};
