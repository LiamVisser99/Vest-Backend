#pragma once

#include <iostream>
#include <iomanip>
#include <array>
#include <string>
#include <algorithm>
#include <cmath>

#include "models/model.hpp"

class engine_manager
{
private:
    int column_count = 0;
    int row_count = 0;
    float radius = 0.0f;

public:
    engine_manager(int cc, int rc, float r) : column_count(cc), row_count(rc), radius(r) {};

    queue_info map_data(const haptic_packet &data);
    queue_container map_pattern(const haptic_layout &data);

    void engine_manager::print_motor_grid(const queue_container& packet);
};

// Eventally I would like to get dynamic radius based on the disatance between points and how large a radius it would take to connect them based on the radius and intensity limited by a certian point

/*
    ex.
        0 0 0 0
        0 0 1 0
        0 0 1 0
        0 0 0 0

        How close are 1 and 1, is it below the max radius and are they close enough at their radius to be considered intersection points (meaning the motors bibrate at the same time)
*/
