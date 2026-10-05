#include <iostream>
#include <chrono>

#include "network/websocket.hpp"
#include "storage/storage.hpp"
#include "haptics/pattern_parser.hpp"
#include "models/model.hpp"
#include "haptics/haptic_engine.hpp"

std::unordered_map<std::string, haptic_layout> memory_cache;

int main()
{
  storage_manager storage;
  websocket_manager websocket;
  parser_manager parser;
  engine_manager engine(4, 5, 0.40f);

  // storage.add_new_file(temp_data);
  // w_manager.websocket_init(11520, "127.0.0.1");

  storage.load_all_patterns(memory_cache);

  auto pattern_it = memory_cache.find("First Haptic Pattern");
  if (pattern_it != memory_cache.end())
  {
    raw_haptic_packet packet = engine.map_pattern(pattern_it->second);

    for (size_t j = 0; j < packet.array_back.size(); j++)
    {
      for (size_t i = 0; i < packet.array_back[j].intensity.size(); ++i)
      {
        std::cout << packet.array_back[j].intensity[i] << ' ';

        if ((i + 1) % 4 == 0)
          std::cout << '\n';
      }

      std::cout << "--------------------\n";
    }

    for (size_t j = 0; j < packet.array_front.size(); j++)
    {
      for (size_t i = 0; i < packet.array_front[j].intensity.size(); ++i)
      {
        std::cout << packet.array_front[j].intensity[i] << ' ';

        if ((i + 1) % 4 == 0)
          std::cout << '\n';
      }

      std::cout << "--------------------\n";
    }
  }
}
