#include "../../include/storage/storage.hpp"

std::vector<std::string> storage_manager::get_missing_files(std::vector<std::string> &file_id)
{
    fs::create_directories(app_dir);

    std::vector<std::string> missing_files;
    for (const auto &id : file_id)
    {
        fs::path full_path = app_dir / (id + ".mod");

        if (!fs::exists(full_path))
        {
            missing_files.push_back(id);
        }
    }

    return missing_files;
}

void storage_manager::add_new_file(std::vector<std::string> &file_data)
{

    for (const auto &file : file_data)
    {

        std::string file_name;

        try
        {
            json haptic_file = json::parse(file);

            file_name = haptic_file["project"]["name"];
        }
        catch (json::parse_error &error)
        {
            std::cerr << "Parsing failed: " << error.what() << std::endl;
        }

        fs::create_directories(app_dir);

        fs::path file_path = app_dir / (file_name + ".mod");

        if (!fs::exists(file_path))
        {
            std::fstream my_file(file_path, std::ios::out | std::ios::in | std::ios::trunc);

            if (my_file.is_open())
            {
                my_file << file;
            }
        }
    }
}