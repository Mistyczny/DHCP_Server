#pragma once
#include "DhcpDatagram.h"
#include "AssignedAddresses.h"
#include <array>

class MessageHandler{
    private:
        DhcpDatagram* datagram;
        AssignedAddresses& assignedAdddresses;
        std::array<char,sizeof(DhcpDatagram)> responseBuffer;
        std::array<char,1024> recvBuffer;
        
        bool process();
        bool createServerResponse();
        bool setResponseConstantParameters();

        bool onDiscover();
        bool onRequest();
        bool onRelease();

        void printMessage();
    public:
        MessageHandler(AssignedAddresses&);
        ~MessageHandler();

        void clear();
        bool createResponse();
        std::array<char,1024>* getBuffer();
        std::array<char,sizeof(DhcpDatagram)>& getResponseBuffer();
        
};