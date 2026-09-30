#include "storage/storage.hpp"

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

json storage_manager::get_file(const std::string &file_id)
{
    fs::create_directories(app_dir);

    fs::path full_path = app_dir / (file_id + ".mod");

    if (!fs::exists(full_path))
    {
        std::cerr << "Could not find file: " << (file_id + ".mod") << std::endl;
        return json{};
    }

    std::ifstream file(full_path);
    try
    {
        return json::parse(file);
    }
    catch (const json::parse_error &error)
    {
        file.close();

        std::cerr << "Parsing failed: " << error.what() << std::endl;
        std::error_code ec;

        fs::remove(full_path, ec);

        if (ec)
        {
            std::cerr << "Failed to delete corrupt file: " << ec.message() << std::endl;
        }

        return json{};
    }
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
            return;
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

void storage_manager::delete_file(const std::string &file_id)
{
    fs::path full_path = app_dir / (file_id + ".mod");

    if (!fs::exists(full_path))
    {
        std::cerr << "Could not find file: " << (file_id + ".mod") << std::endl;
        return;
    }
    std::error_code ec;

    fs::remove(full_path, ec);

    if (ec)
    {
        std::cerr << "Failed to delete corrupt file: " << ec.message() << std::endl;
    }
}

haptic_layout storage_manager::load_file_to_memory(const std::string &file_id)
{
    fs::create_directories(app_dir);

    fs::path full_path = app_dir / (file_id + ".mod");

    if (!fs::exists(full_path))
    {
        std::cerr << "Could not find file: " << (file_id + ".mod") << std::endl;
        // return {};
    }
    parser_manager parser;

    std::ifstream file(full_path);
    try
    {
        json data = json::parse(file);

        return parser.parse_file(data);
    }
    catch (const json::parse_error &error)
    {
        std::cerr << "Parsing failed: " << error.what() << std::endl;
    }
}

void storage_manager::load_all_patterns(std::unordered_map<std::string, haptic_layout> &memory_cache)
{
    fs::create_directories(app_dir);

    parser_manager parser;

    for (const auto &entry : fs::directory_iterator(app_dir))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".mod")
        {
            std::string file_id = entry.path().stem().string();

            haptic_layout data = parser.parse_file(get_file(file_id));

            memory_cache[file_id] = data;
        }
    }
}