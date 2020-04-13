#pragma once

namespace MessageError{
    enum errorCode{
        UNKOWN_ERROR = 1,
        SERVER_RECEIVED_RESPONSE_OPCODE,
        WRONG_OPCODE_CODE,
        BAD_HARDWARE_TYPE_CODE
    };
}