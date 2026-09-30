#include "haptics/haptic_engine.hpp"
#include "models/model.hpp"

/*
void engine_manager::map_pattern(const model::haptic_pattern_data& data)
{
    raw_haptic_packet packet{};

    for(const auto& row : row_count)
    {
        for(const auto& col : column_count)
        {
            float n_x = row / (float)(row_count - 1);
            float n_y = col / (float)(column_count - 1);

            float distance = std::sqrtf((std::pow((n_x - data.x_coord), 2) + std::pow((n_y - data.y_coord), 2)));

            int index = (row * column_count + col);
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
    */