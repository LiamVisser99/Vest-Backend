#pragma once

#include <cmath>
#include <vector>
#include <iostream>

constexpr int col_X = 5;
constexpr int row_y = 4;
constexpr int update_rate = 5000;

class engine_manager
{
    private:
    public: 
    void map_pattern(const auto& data);
};

// The gloal is to map a part of the pattern to data the vest can undertstand, fill a struct, and send over bluetooth