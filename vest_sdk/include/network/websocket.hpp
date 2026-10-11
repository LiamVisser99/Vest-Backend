#pragma once

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocketServer.h>
#include <nlohmann/json.hpp>

#include "models/model.hpp"

using json = nlohmann::json;

class websocket_manager
{
private:

public:
    void request_file(ix::WebSocket& websocket, const std::vector<std::string>& file_id);
    void valid_files(ix::WebSocket& websocket);
    void binary_haptic_packet(const uint8_t* buffer, size_t length);
    void init(const int &websocket_port, const std::string websocket_host);
};