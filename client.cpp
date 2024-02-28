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
#include "client.h"

enum MessageType : uint32_t{
    Read,
    All,
    Other,
};

class client : public client_interface<MessageType>{
    protected:
        void HandleMessage(const Message<MessageType>& msg){

            Message<MessageType> ms = msg;
            int a, b;
            char c[5];

            ms >> a >> c >>b;

            std::cout << a << " " << c << " " << b << "\n";
        }
};

int main(){

    client cl;

    Message<MessageType> ms;
    int a = 12;
    int b = 25;
    char c[5] = "name";

    ms.head = {Read, 0};
    ms << a << c << b;

    cl.Connect("127.0.0.1", 10000);

    ms.head.id = MessageType::Other;

    char input;
    while(1){

        //std::cin.get();
        std::cin >> input;
        if(input == 'a'){
            cl.Send(ms);
        }
        cl.Update();
    }

    return 0;
}