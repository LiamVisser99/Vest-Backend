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
  engine_manager engine(4, 5, 0.80f);

  // storage.add_new_file(temp_data);
  // w_manager.websocket_init(11520, "127.0.0.1");

  storage.load_all_patterns(memory_cache);

  auto pattern_it = memory_cache.find("First Haptic Pattern");
  if (pattern_it != memory_cache.end())
  {
    raw_haptic_packet packet = engine.map_pattern(pattern_it->second);

    int i = 0;

for (const auto& data : packet.array_back)
{
    for (size_t i = 0; i < data.intensity.size(); ++i)
    {
        std::cout << data.intensity[i] << ' ';

        if ((i + 1) % 4 == 0)
            std::cout << '\n';
    }

    std::cout << "--------------------\n";
}
  }
}