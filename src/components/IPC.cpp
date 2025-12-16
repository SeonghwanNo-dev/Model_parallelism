#include <iostream>
#include <string>
#include <arpa/inet.h>  // sockaddr_in, inet_addr(), ...
#include <sys/socket.h> // socket(), connect(), ...
#include <unistd.h>     // close()


using namespace std;

class IPC{
private:
    int connected_node_socket;
    string connected_node_address;
public:
    void ConnectNode(string target_address);
    // void CheckConnection();
    // void TransmitData(pyt_data data);
    // void DisconnectNode();
};


void IPC::ConnectNode(string target_address){
    // input(target_address) format: 0832.8943.3849.3934:239
    
    string ip = "";
    string port = "";
    string temp;

    // parse target_address into ip, port
    int parsing_port = 0;
    for (char c : target_address) {
        if (c == ':')
        {
            parsing_port = 1;
            continue;
        }
        if (parsing_port == 1)
            port+=c;
        else ip+=c;
    }


    // check if target_address is valid
    // check 1: size check
    if (ip.size() != 19) 
    {
        cout<<"Invalid input: Make input format xxxx.xxxx.xxxx.xxxx:xxx";
        return;
    }    
    // check 2: valid alphanumeric or special character
    for (int i=0; i<(int) ip.size(); i++)
    {
        if (i==4 || i == 9 || i==14)
        {
            if (ip[i]!='.')
            {
                cout << "Invalid input: Expected '.' at the correct position." << endl;
                return;
            }
            else continue;
        }

        if (isxdigit(ip[i])) continue;
        else 
        {   
            cout<<" Invalid input: Each character in the IP must be a valid alphanumeric or special character.\n";
            return;
        }
    }
    for (auto i:port)
    {
        if (isxdigit(i)) continue;
        else 
        {
            cout<<"Invalid input: Each character in the PORT must be a valid alphanumeric or special character.\n";
            return;
        }
    }
    cout<< "Address format check complete\n";

    // Socket Code Area
    // 1. Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        cout << "Connection fail (Socket creation error)" << endl;
        return;
    }
    // 2. Configure the target node's address structure
    struct sockaddr_in target_node_addr;
    memset(&target_node_addr, 0, sizeof(target_node_addr)); // Initialize memory
    target_node_addr.sin_family = AF_INET;                 // IPv4
    target_node_addr.sin_addr.s_addr = inet_addr(ip); // Target Node IP
    target_node_addr.sin_port = htons(stoi(port));         // Target Node Port
    // 3. Attempt to establish a network connection to the target node
    if (connect(sock, (struct sockaddr*)&target_node_addr, sizeof(target_node_addr)) == -1) {
        cout << "Connection fail" << endl;
        // Close the socket to release the file descriptor
        close(sock);
        return;
    }
    // 4. Handle successful connection to the target node
    this->connected_node_socket = sock; 
    this->connected_node_address = ip+':'+port;
    cout << "Connection established successfully." << endl;

    // 실험해본 뒤(가능하면) push ㄱㄱ

}


int main()
{
    string add = "1243.2324.2323.2433:2s2";
    IPC ipc;
    ipc.ConnectNode(add);
    return 0;
}