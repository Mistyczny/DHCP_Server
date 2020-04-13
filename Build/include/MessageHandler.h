#pragma once
#include "DhcpDatagram.h"
#include "AddressesElector.h"
#include <array>

class MessageHandler{
    private:
        int errorCode;
        std::array<char,548> recvBuffer;
        DhcpDatagram* datagram;
        AddressesElector& occupiedAddrs;
        DhcpDatagram responseDatagram;

        void process();
        void createServerResponse();
        bool setResponseConstantParameters();
        void assignClientNewAddress();

        void onDiscover();
        void onRequest();
        void onRelease();
    public:
        MessageHandler(AddressesElector& addr);
        ~MessageHandler();

        std::array<char,548>* getBuffer();

        bool createResponse();
        DhcpDatagram& getResponse();
};