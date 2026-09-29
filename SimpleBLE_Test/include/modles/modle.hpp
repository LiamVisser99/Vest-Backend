#pragma once

#pragma pack(push, 1)
struct haptic_packet
{
    float xCoord;
    float yCoord;
    float intensity;
    float radius;
    unsigned short duration;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct motor_data
{
    uint16_t intensity;
    uitn16_t duration;
}

struct raw_haptic_packet
{
    std::vector<motor_data> array_front;
    std::vector<motor_data> array_back;
}
#pragma pack(pop)