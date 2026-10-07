#include <iostream>
#include <chrono>
#include <thread>

#include "network/websocket.hpp"
#include "storage/storage.hpp"
#include "haptics/pattern_parser.hpp"
#include "models/model.hpp"
#include "haptics/haptic_engine.hpp"
#include "network/bluetooth.hpp"

namespace
{
  connection_info settings{};
}


std::unordered_map<std::string, haptic_layout> memory_cache;

int main()
{
  storage_manager storage;
  websocket_manager websocket;
  bluetooth_manager bluetooth;
  parser_manager parser;
  engine_manager engine(4, 5, 0.80f);

  // storage.add_new_file(temp_data);
  std::thread ble([&bluetooth]()
                  { bluetooth.init(); });
  ble.detach();
  websocket.init(11520, "127.0.0.1");

  storage.load_all_patterns(memory_cache);

  auto pattern_it = memory_cache.find("First Haptic Pattern");
  if (pattern_it != memory_cache.end())
  {
    raw_haptic_packet packet = engine.map_pattern(pattern_it->second);
  }

  std::this_thread::sleep_for(std::chrono::seconds(5));

  motor_data packet = {2000, 20};

  bluetooth.send_haptic_message(packet);
}