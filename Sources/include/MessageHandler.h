#pragma once
#include "DhcpDatagram.h"
#include "AssignedAddresses.h"
#include "AddressesElector.h"
#include <array>

class MessageHandler{
    private:
        int errorCode;
        DhcpDatagram* datagram;
        AssignedAddresses& assignedAdddresses;
        std::array<char,sizeof(DhcpDatagram)> responseBuffer;
        std::array<char,1024> recvBuffer;
        
        void process();
        void createServerResponse();
        bool setResponseConstantParameters();

        void onDiscover();
        void onRequest();
        void onRelease();

        void printMessage();
    public:
        MessageHandler(AssignedAddresses&);
        ~MessageHandler();

        void clear();
        bool createResponse();
        std::array<char,1024>* getBuffer();
        std::array<char,sizeof(DhcpDatagram)>& getResponseBuffer();
        
};