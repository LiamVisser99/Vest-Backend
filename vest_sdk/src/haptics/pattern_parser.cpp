#include "haptics/pattern_parser.hpp"

haptic_layout parser_manager::parse_file(const json &file)
{
    haptic_layout packet_data{};

    const json &data = file;

    auto &layouts = data["project"]["layout"]["layouts"];

    for (const auto &item : layouts["VestBack"])
    {
        haptic_packet packet{};

        packet.duration = item["duration"];
        packet.intensity = item["intensity"];
        packet.x_coord = item["x"];
        packet.y_coord = item["y"];

        packet_data.back.push_back(packet);
    }

    for (const auto &item : layouts["VestFront"])
    {
        haptic_packet packet{};

        packet.duration = item["duration"];
        packet.intensity = item["intensity"];
        packet.x_coord = item["x"];
        packet.y_coord = item["y"];

        packet_data.front.push_back(packet);
    }

    return packet_data;
}