#pragma once

#include <iostream>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>

#include <simpleble/SimpleBLE.h>

#include "models/model.hpp"

struct connection_info
{
static constexpr int pairing_time = 5000;
static constexpr std::string_view adapter_type = "TP-Link";
static inline const SimpleBLE::ByteArray manufacturer_tag = {0x6d, 0x6f, 0x64, 0x75, 0x65, 0x78};
static inline const SimpleBLE::BluetoothUUID characteristic_uuid = "12345678-1234-5678-1234-56789abcdef1";   
static inline const SimpleBLE::BluetoothUUID service_uuid = "12345678-1234-5678-1234-56789abcdef0";
};

class bluetooth_manager
{
private:
    SimpleBLE::Adapter adapter_;
    SimpleBLE::Peripheral peripheral_;

    SimpleBLE::Adapter get_preferred_adapter();
    SimpleBLE::Peripheral get_preferred_device(SimpleBLE::Adapter &adapter);
    std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>> get_preferred_device_characteristics(SimpleBLE::Peripheral &peripheral);

public:
    void init();
    void send_haptic_message(const raw_haptic_packet& data);
};