#include "haptics/haptic_engine.hpp"

// Currently the radius is fixed but that will hopefuly be changed in the future

motor_data engine_manager::map_data(const haptic_packet &data)
{
    size_t constructor_size = row_count * column_count;
    motor_data packet(constructor_size, constructor_size);

    for (int row = 0; row < row_count; ++row)
    {
        for (int col = 0; col < column_count; ++col)
        {
            float n_x = col / (float)(column_count - 1);
            float n_y = row / (float)(row_count - 1);

            float distance = std::sqrtf((std::pow((n_x - data.x_coord), 2) + std::pow((n_y - data.y_coord), 2)));

            int index = (row * column_count + col);
            if (distance <= radius)
            {
                float linear_remap = 1.0f - (distance / radius);
                float smoothstep_remap = data.intensity * ((linear_remap * linear_remap) * (3.0f - (2.0f * linear_remap)));

                packet.intensity[index] += smoothstep_remap;
                packet.intensity[index] = std::clamp<float>(packet.intensity[index], 0.0f, 4095.0f);
                packet.duration[index] = data.duration;
            }
        }
    }

    return packet;
}

raw_haptic_packet engine_manager::map_pattern(const haptic_layout& data)
{
    size_t constructor_size = row_count * column_count;
    raw_haptic_packet packet;

    for (size_t index = 0; index < data.front.size(); ++index)
    {
        packet.array_front.push_back(map_data(data.front[index]));
    }

    for (size_t index = 0; index < data.back.size(); ++index)
    {
        packet.array_back.push_back(map_data(data.back[index]));
    }

    return packet;
}