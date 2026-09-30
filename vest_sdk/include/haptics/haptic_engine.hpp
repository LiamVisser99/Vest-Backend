#pragma once

#include <cmath>
#include <vector>
#include <iostream>

class engine_manager
{
private:
    const int column_count = 5;
    const int row_count = 4;
    const int update_rate = 5000;

public:
    void map_pattern(const haptic_layout&data);
};

// The gloal is to map a part of the pattern to data the vest can undertstand, fill a struct, and send over bluetooth