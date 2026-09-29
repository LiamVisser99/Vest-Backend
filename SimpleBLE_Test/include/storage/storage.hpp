#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <string>
#include <vector>

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
    void add_new_file(std::vector<std::string> &file_data);
};