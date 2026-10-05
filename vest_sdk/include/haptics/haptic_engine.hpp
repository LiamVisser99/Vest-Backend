#pragma once

#include <cmath>
#include <vector>
#include <iostream>

#include "../storage/storage.hpp"
#include "../models/model.hpp"

class engine_manager
{
private:
    int column_count;
    int row_count;
    float radius;

public:
    engine_manager(int cc, int rc, float r) : column_count(cc), row_count(rc), radius(r) {};

    motor_data map_data(const haptic_packet &data);
    raw_haptic_packet map_pattern(const haptic_layout& data);
};
