#pragma once

#include <string_view>

#include <simpleble/SimpleBLE.h>

struct connection_info
{
    const int pairing_time = 5000;
    const std::string_view adapter_type = "TP-Link";
    const SimpleBLE::ByteArray manufacturer_tag = {0x6d, 0x6f, 0x64, 0x75, 0x65, 0x78};
};

class bluetooth_manager
{
public:
    void initialize();
};