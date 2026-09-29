#include "../include/haptics/haptic_engine.hpp"
#include "../include/modles/modle/cpp"

void engine_manager::map_pattern(const auto& data)
{
    raw_haptic_packet packet{};

    for(const auto& row : row_X)
    {
        for(const auto& col : col_Y)
        {
            float nX = row / (float)(row_X - 1);
            float nY = col / (float)(col_X - 1);

            float distance = std::sqrtf((std::pow((nX - data.xCoord), 2) + std::pow((nY - data.yCoord), 2)));

            int index = (row * col_Y + col);
            if(distance <= data.radius)
            {
                float linear_remap = 1.0f - (distance / data.radius);
                float smoothstep_remap = data.intensity * ((linear_remap * linear_remap) * (3.0f - (2.0f * linear_remap)));

                packet.array_front[index].intensity += smoothstep_remap;
                packet.array_front[index].intensity = std::clamp(packet.array_front[index].intensity, 0, 4095.0f);
                packet.array_front[index].duration = data.duration;
                
                packet.array_back[index].intensity += smoothstep_remap;
                packet.array_back[index].intensity = std::clamp(packet.array_back[index].intensity, 0, 4095.0f);
                packet.array_back[index].duration = data.duration;
            }
        }
    }

    return packet;
}