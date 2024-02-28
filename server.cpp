#include <iostream>
#include <vector>
#include <thread>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif
#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/buffer.hpp>

#include "message.h"
#include "server.h"


enum MessageType : uint32_t{
    Read,
    All,
    Other,
};

class server : public server_interface<MessageType>{
    public:
        //server(){}

    protected:
        void HandleMessage(std::shared_ptr<connection<MessageType>> client, const Message<MessageType>& msg){

            if(msg.head.id == MessageType::All){
                SendAll(msg);
            }
            else if(msg.head.id == MessageType::Other){
                SendAll(msg, client);
            }else{
                Send(client, msg);
            }
            std::cout << "MESSAGE HANDLED\n";
        }
};

int main(){
    
    server sv;
    
    sv.start();

    while(1){
        sv.Update();
    }

    return 0;
}