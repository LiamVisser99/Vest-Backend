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
    const connection_info settings{};
}

std::unordered_map<std::string, haptic_layout> memory_cache;

int main()
{
  storage_manager storage;
  websocket_manager websocket;
  bluetooth_manager bluetooth;
  parser_manager parser;
  engine_manager engine(4, 5, 0.80f);

  storage.load_all_patterns(memory_cache);
  auto pattern_it = memory_cache.find("First Haptic Pattern");

  std::thread web([&websocket]()
                  { websocket.init(11520, "127.0.0.1"); });
  web.detach();

  /*
  std::thread ble([&bluetooth]()
                  { bluetooth.init(); });
  ble.detach();
  */

  std::this_thread::sleep_for(std::chrono::milliseconds(settings.pairing_time + 100));

  queue_container packet{};
  if (pattern_it != memory_cache.end())
  {
    packet = engine.map_pattern(pattern_it->second);
  }
  engine.print_motor_grid(packet);
}