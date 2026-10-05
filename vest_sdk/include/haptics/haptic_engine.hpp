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

    motor_data map_data(const haptic_packet& data);
    raw_haptic_packet map_pattern(const haptic_layout& data);
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
