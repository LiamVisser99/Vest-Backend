#pragma once

#include <cstdint>
#include <vector>
#include <queue>

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

struct motor_data
{
    std::vector<uint16_t> intensity;
    std::vector<uint16_t> duration;

    motor_data(size_t is, size_t ds) : intensity(is), duration(ds) {}
};

struct raw_haptic_packet
{
    std::vector<motor_data> array_front;
    std::vector<motor_data> array_back;
};

struct queue
{
    std::vector<std::queue<raw_haptic_packet>> packets;
};