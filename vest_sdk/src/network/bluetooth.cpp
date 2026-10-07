#include "network/bluetooth.hpp"

namespace
{
    const connection_info settings{};
}

SimpleBLE::Adapter bluetooth_manager::get_preferred_adapter()
{
    auto adapters = SimpleBLE::Adapter::get_adapters();
    for (auto &adapter : adapters)
    {
        if (adapter.identifier().find(settings.adapter_type) != std::string::npos)
        {
            return adapter;
        }
    }

    if (!adapters.empty())
    {
        std::cerr << "Preferred bluetooth adapter was not found." << std::endl;
        return adapters[0];
    }

    std::cerr << "No adapters were found" << std::endl;
    std::exit(EXIT_FAILURE);
}

SimpleBLE::Peripheral bluetooth_manager::get_preferred_device(SimpleBLE::Adapter &adapter)
{
    std::vector<SimpleBLE::Peripheral> peripherals;

    adapter.set_callback_on_scan_start([]()
                                       { std::cout << "Scan started." << std::endl; });
    adapter.set_callback_on_scan_stop([]()
                                      { std::cout << "Scan stopped." << std::endl; });
    adapter.set_callback_on_scan_found([&](SimpleBLE::Peripheral peripheral)
                                       {
    
                                        std::map<uint16_t, SimpleBLE::ByteArray> manufacturer_data = peripheral.manufacturer_data();

        for (const auto &[manufacturer_id, data] : manufacturer_data)
        {
            std::string data_str(data.begin(), data.end());
            std::string manufacturer_tag_str(settings.manufacturer_tag.begin(), settings.manufacturer_tag.end());
            if (data_str == manufacturer_tag_str && peripheral.is_connectable())
            {
                std::cout << "Found device: " << peripheral.identifier() << " [" << peripheral.address() << "]" << std::endl;
                peripherals.push_back(peripheral);
            }
        } });

    adapter.scan_for(settings.pairing_time);

    if (peripherals.empty())

    {
        std::cerr << "No connectable perpherials were found." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    size_t peripheral_index = 0;

    std::cout << "Connectable devices:" << std::endl;
    for (size_t i = 0; i < peripherals.size(); i++)
    {
        std::cout << "[" << i << "] " << peripherals[i].identifier() << " [" << peripherals[i].address() << "]" << std::endl;
    }

    std::cout << "Select a device to connect too (0-" << peripherals.size() - 1 << "): " << std::endl;

    std::cin >> peripheral_index;

    if (!std::cin || peripheral_index > peripherals.size())
    {
        std::cerr << "Invalid peripheral selection." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return peripherals[peripheral_index];
}

std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>> bluetooth_manager::get_preferred_device_characteristics(SimpleBLE::Peripheral &peripheral)
{
    std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>> temp_readable_characteristics;

    for (auto &service : peripheral.services())
    {
        for (auto &characteristic : service.characteristics())
        {
            if (characteristic.can_read())
            {
                temp_readable_characteristics.emplace_back(service.uuid(), characteristic.uuid());
            }
        }
    }

    if (temp_readable_characteristics.empty())
    {
        std::cerr << "The peripheral has no readable charcteristics." << std::endl;
        peripheral.disconnect();
        std::exit(EXIT_FAILURE);
    }

    return temp_readable_characteristics;
}

void bluetooth_manager::send_haptic_message(const motor_data &data)
{
    SimpleBLE::ByteArray payload(reinterpret_cast<const char*>(&data), sizeof(data));

    peripheral_.write_command(settings.service_uuid, settings.characteristic_uuid, payload);
}

void bluetooth_manager::init()
{
    if (!SimpleBLE::Adapter::bluetooth_enabled())
    {
        std::cerr << "Bluetooth is not enabled or permission has not been granted." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Bluetooth is available" << std::endl;
    }

    adapter_ = get_preferred_adapter();
    std::cout << "Using adapter: " << adapter_.identifier() << " [" << adapter_.address() << "]" << std::endl;

    peripheral_ = get_preferred_device(adapter_);
    std::cout << "Connecting to " << peripheral_.identifier() << " [" << peripheral_.address() << "]" << std::endl;
    peripheral_.connect();

    std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>> readable_characteristics = get_preferred_device_characteristics(peripheral_);

    std::cout << "Readable characteristics: " << std::endl;
    for (size_t i = 0; i < readable_characteristics.size(); i++)
    {
        std::cout << "[" << i << "] " << readable_characteristics[i].first << " " << readable_characteristics[i].second << std::endl;
    }
}

// This file is a mess and needs to be refactored to work alone