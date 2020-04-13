#pragma once
#include "DhcpDatagram.h"
#include "NetworkAddresses.h"

class ClientRequestHandler{
    private:
        int errorCode;
        std::array<char,548> recvBuffer;
        DhcpDatagram* datagram;
        NetworkAddresses& addresses;
        DhcpDatagram datagramResponse;
        DhcpDatagram responseDatagram;

        void onReplyMessage();
        void onRequestMessage();
        void process();
        void rewriteDataToResponse();
        void fillWithDynamicData();
        bool isClientAddressProvided();

        void onClientAddressOwn();
        void onClientWithoutAddress();

        void handleException(std::exception& ex);
    public:
        ClientRequestHandler(NetworkAddresses&);
        virtual ~ClientRequestHandler();
        
        void setResponseHardwareType();

        void start();
        bool processDatagram();

        std::array<char,548>* getBuffer();
        void justPrint(){
            std::cout<<"RANDOM PRONT"<<std::endl;
        }
};