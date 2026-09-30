#include <iostream>

#include "network/websocket.hpp"
#include "storage/storage.hpp"
#include "haptics/pattern_parser.hpp"
#include "models/model.hpp"

std::unordered_map<std::string, haptic_layout> memory_cache;

int main()
{
  storage_manager storage;
  websocket_manager websocket;
  parser_manager parser;

  // storage.add_new_file(temp_data);
  // w_manager.websocket_init(11520, "127.0.0.1");
  // First Haptic Pattern

  storage.load_all_patterns(memory_cache);

  for (const auto& [file_id, layout] : memory_cache) 
    {
        std::cout << "ID: " << file_id 
                  << " | Front Packets: " << layout.front.size() 
                  << " | Back Packets: " << layout.back.size() 
                  << std::endl;
      for (const auto &packet : layout.back)
      {
        std::cout << packet.intensity << "\t";
      }
    }
}