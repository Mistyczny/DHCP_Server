#pragma once

namespace DHCP_Defines{
    enum opcode {
        Client_message = 1,
        Server_message
    };

    enum MessageType{
        Discover = 1,
        Offer,
        Request,
        Decline,
        Ack,
        NAK,
        Release,
        Inform,
        Force_Renew
    };
}