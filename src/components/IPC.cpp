#include <iostream>
#include <string>

using namespace std;

class IPC{
private:
    // node connected_node;
    // string connected_node_address;
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
        if (c == '.') continue;
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
    if (ip.size() != 16) 
    {
        cout<<"Invalid input\n"<<"Make input format xxxx.xxxx.xxxx.xxxx:xxx";
        return;
    }    
    // check 2: valid alphanumeric or special character
    for (auto i:ip)
    {
        if (isxdigit(i)) continue;
        else 
        {   
            cout<<"Invalid input\n"<<"Each character in the IP must be a valid alphanumeric or special character.\n";
            return;
        }
    }
    for (auto i:port)
    {
        if (isdigit(i)) continue;
        else if (isalpha(i)) continue;
        else 
        {
            cout<<"Invalid input\n"<<"Each character in the PORT must be a valid alphanumeric or special character.\n";
            return;
        }
    }
    cout<< "Address format check complete\n";



}

int main()
{
    string add = "1243.23s4.2323.32433:2s2";
    IPC ipc;
    ipc.ConnectNode(add);
    return 0;
}