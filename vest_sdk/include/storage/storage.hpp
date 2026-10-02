#pragma once

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>
#include "../haptics/pattern_parser.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

class storage_manager
{
private:
    fs::path app_dir;

public:
    storage_manager()
    {
        const char* appdata_path = std::getenv("APPDATA");
        if (appdata_path) 
        {
            app_dir = fs::path(appdata_path) / "Haptic_Patterns";
        }
    }

    std::vector<std::string> get_missing_files(std::vector<std::string> &file_id);
    haptic_layout load_file_to_memory(const std::string &file_id);
    void load_all_patterns(std::unordered_map<std::string, haptic_layout>& memory_cache);

    json get_file(const std::string &file_name);
    void add_new_file(std::vector<std::string> &file_data);
    void delete_file(const std::string &file_id);
};

//You may be lost tommorow, basically I made a system that stores a hash map of the pre-parsed data from each file all at once upon strtup. I have the raw code in the main.cpp,
//however, I need to make a system that allows me to add new files during runtime (I assume that will be via load_file_to_memory (im to tired to think)) and theoretically delete
//lodaded files from cache aswell. I need to encapusulate the data in the main in a function, I assume it will go in pattern_parser or storage. Good luck!