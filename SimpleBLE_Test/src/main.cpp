#include <iostream>
#include "../include/storage/storage.hpp"
#include "../include/network/websocket.hpp"

int main()
{
    storage_manager s_manager;
    websocket_manager w_manager;

    std::vector<std::string> temp_data;

    temp_data.push_back(R"({
  "project": {
    "createdAt": 1790465677392,
    "description": "The First Moduex Haptic Pattern!",
    "layout": {
      "layouts": {
        "VestBack": [
          { "index": 0, "duration": 66.67, "intensity": 1, "x": 0, "y": 0 },
          { "index": 1, "duration": 66.67, "intensity": 1, "x": 0.333, "y": 0 },
          { "index": 2, "duration": 66.67, "intensity": 1, "x": 0.667, "y": 0 },
          { "index": 3, "duration": 66.67, "intensity": 1, "x": 1, "y": 0 },
          { "index": 4, "duration": 66.67, "intensity": 1, "x": 0, "y": 0.333 },
          { "index": 5, "duration": 66.67, "intensity": 1, "x": 0.333, "y": 0.333 },
          { "index": 6, "duration": 66.67, "intensity": 1, "x": 0.667, "y": 0.333 },
          { "index": 7, "duration": 66.67, "intensity": 1, "x": 1, "y": 0.333 },
          { "index": 8, "duration": 66.67, "intensity": 1, "x": 0, "y": 0.667 },
          { "index": 9, "duration": 66.67, "intensity": 1, "x": 0.333, "y": 0.667 },
          { "index": 10, "duration": 66.67, "intensity": 1, "x": 0.667, "y": 0.667 },
          { "index": 11, "duration": 66.67, "intensity": 1, "x": 1, "y": 0.667 },
          { "index": 12, "duration": 66.67, "intensity": 1, "x": 0, "y": 1 },
          { "index": 13, "duration": 66.67, "intensity": 1, "x": 0.333, "y": 1 },
          { "index": 14, "duration": 66.67, "intensity": 1, "x": 0.667, "y": 1 },
          { "index": 15, "duration": 66.67, "intensity": 1, "x": 1, "y": 1 }
        ],
        "VestFront": [
          { "index": 16, "duration": 66.67, "intensity": 1, "x": 0, "y": 0 },
          { "index": 17, "duration": 66.67, "intensity": 1, "x": 0.333, "y": 0 },
          { "index": 18, "duration": 66.67, "intensity": 1, "x": 0.667, "y": 0 },
          { "index": 19, "duration": 66.67, "intensity": 1, "x": 1, "y": 0 },
          { "index": 20, "duration": 66.67, "intensity": 1, "x": 0, "y": 0.333 },
          { "index": 21, "duration": 66.67, "intensity": 1, "x": 0.333, "y": 0.333 },
          { "index": 22, "duration": 66.67, "intensity": 1, "x": 0.667, "y": 0.333 },
          { "index": 23, "duration": 66.67, "intensity": 1, "x": 1, "y": 0.333 },
          { "index": 24, "duration": 66.67, "intensity": 1, "x": 0, "y": 0.667 },
          { "index": 25, "duration": 66.67, "intensity": 1, "x": 0.333, "y": 0.667 },
          { "index": 26, "duration": 66.67, "intensity": 1, "x": 0.667, "y": 0.667 },
          { "index": 27, "duration": 66.67, "intensity": 1, "x": 1, "y": 0.667 },
          { "index": 28, "duration": 66.67, "intensity": 1, "x": 0, "y": 1 },
          { "index": 29, "duration": 66.67, "intensity": 1, "x": 0.333, "y": 1 },
          { "index": 30, "duration": 66.67, "intensity": 1, "x": 0.667, "y": 1 },
          { "index": 31, "duration": 66.67, "intensity": 1, "x": 1, "y": 1 }
        ]
      },
      "device_name": "Vibe_V1",
      "device_type": "Vest"
    },
    "hapticFileDuration": 2,
    "name": "I am the sigma!"
  }
}
)");

    s_manager.add_new_file(temp_data);
    w_manager.websocket_init(11520, "127.0.0.1");
    
}