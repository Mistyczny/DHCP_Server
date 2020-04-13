#include "MessageUtilities.h"

namespace MessageUtilities{
    bool isClientMessage(std::byte& byte){
        return std::to_integer<int>(byte) == DHCP_Defines::Client_message;
    }
}