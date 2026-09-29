#include <iostream>

#include <nlohmann/json.hpp>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocketServer.h>

using json = nlohmann::json;

class websocket_manager
{
private:

public:
    void request_file(ix::WebSocket &webSocket, const std::vector<std::string> &file_id);
    void valid_files(ix::WebSocket &webSocket);
    void binary_haptic_packet(ix::WebSocket &webSocket, const uint8_t* buffer, size_t length);
    void websocket_init(const int &websocket_port, const std::string websocket_host);
};