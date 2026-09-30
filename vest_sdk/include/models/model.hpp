#pragma once

#include <cstdint>
#include <vector>

struct haptic_packet
{
    float x_coord;
    float y_coord;
    float intensity;
    uint16_t duration;
};

struct haptic_layout
{
    std::vector<haptic_packet> front;
    std::vector<haptic_packet> back;
};

#pragma pack(push, 1)
struct motor_data
{
    uint16_t intensity;
    uint16_t duration;
};
#pragma pack(pop)

struct raw_haptic_packet
{
    std::vector<motor_data> array_front;
    std::vector<motor_data> array_back;
};