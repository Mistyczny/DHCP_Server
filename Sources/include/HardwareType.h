#pragma once
#include <cstddef>

namespace HardwareTypes{
    enum{
        Ethernet = 1,
        Experiemental_Ethernet,
        AX_25,
        Proteon_Token_Ring,
        Chaos,
        IEEE_802,
        Arcnet,
        Hyperchannel,
        Lanstar,
        Autonet_Short_Address,
        LocalTalk,
        LocalNet,
        Ultra_Link,
        SMDS,
        Frame_Relay,
        ATM_16,
        HDLC,
        Fibre_Channel,
        ATM_19,
        Serial_Line,
        ATM_21,
        MIL_STD_188_220,
        Metricom,
        IEEE_1394,
        MAPOS,
        Twinaxial,
        EUI_64,
        HIPARP,
        IP_Over_ISO_7816_3,
        ARPSec,
        IPSec_Tunnel,
        Infiniband,
        CAI_TIA_102
    };

    bool isCorrect(std::byte byte){
        int hType = std::to_integer<int>(byte);
        return (hType>=1 && hType<=33);
    }
}