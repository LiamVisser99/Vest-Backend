#pragma once

#pragma pack(push, 1)
struct haptic_packet
{
    float xCoord;
    float yCoord;
    float intensity;
    unsigned short duration;
};
#pragma pack(pop)