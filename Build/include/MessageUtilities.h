#pragma once
#include "DhcpDefines.h"
#include <cstddef>

namespace MessageUtilities{
    bool isClientMessage(std::byte& byte);
}