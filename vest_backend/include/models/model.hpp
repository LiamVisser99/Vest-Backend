#pragma once

#include <cstdint>
#include <vector>
#include <array>

inline constexpr std::size_t motor_array_size = 20;

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

struct queue_info
{
    std::array<uint16_t, motor_array_size> intensity;
    std::array<uint16_t, motor_array_size> duration;
};

struct queue_container
{
    std::vector<queue_info> array_front;
    std::vector<queue_info> array_back;
};

#pragma pack(push, 1)
struct raw_haptic_packet
{
    std::array<uint16_t, motor_array_size> array_front;
    std::array<uint16_t, motor_array_size> array_back;
};
#pragma pack(pop)