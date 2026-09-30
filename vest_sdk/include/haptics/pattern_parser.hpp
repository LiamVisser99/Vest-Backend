#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include <iostream>

#include "models/model.hpp"

using json = nlohmann::json;

class parser_manager
{
private:
public:
    haptic_layout parse_file(const json& file);
};

// The goal is to call on a haptic file to play, where it is subsequetly loaded from haptic_pattern (folder) and parsed and loaded into the engine in a timley manner via structs