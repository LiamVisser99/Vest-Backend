#include "haptics/haptic_engine.hpp"

queue_info engine_manager::map_data(const haptic_packet &data)
{
    queue_info packet{};

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

queue_container engine_manager::map_pattern(const haptic_layout &data)
{
    size_t constructor_size = row_count * column_count;
    queue_container packet;

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

void engine_manager::print_motor_grid(const queue_container& packet)
{
    for(size_t j = 0; j < packet.array_front.size(); j++)
    {
        const auto& front = packet.array_front[j].intensity;
        const auto& back = packet.array_back[j].intensity;

        std::cout << "\t " << "Front" << "\t\t\t" << "Back" << '\n';

        for (size_t i = 0; i < front.size(); i++)
        {
            std::cout << std::setw(4) << front[i] << " ";

            if(i % column_count == column_count - 1)
            {
                std::cout << " | ";

                size_t row_start = i + 1 - column_count;

                for (size_t k = row_start; k <= i && k < back.size(); k++)
                {
                    std::cout << std::setw(4) << back[k] << " ";
                }

                std::cout << "\n";
            }
        }
        std::cout << "\n";
    }
}