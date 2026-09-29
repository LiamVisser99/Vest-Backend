#include <iostream>

#include "../../include/storage/storage.hpp"
#include "../../include/network/websocket.hpp"
#include "../../include/modles/modle.hpp"
#include <nlohmann/json.hpp>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocketServer.h>

using json = nlohmann::json;

void websocket_manager::request_file(ix::WebSocket &webSocket, const std::vector<std::string> &file_id)
{
    json request = {
        {"action", "get missing file"},
        {"id", file_id}};

    std::cout << "Payload sent: " << request << std::endl;
    webSocket.send(std::move(request.dump()));
}

void websocket_manager::valid_files(ix::WebSocket &webSocket)
{
    json request = {
        {"action", "all files valid"}};

    std::cout << "Payload sent: " << request << std::endl;
    webSocket.send(std::move(request.dump()));
}

void websocket_manager::binary_haptic_packet(ix::WebSocket &webSocket, const uint8_t* buffer, size_t length)
{
    if(length ==  sizeof(haptic_packet))
    {
        haptic_packet packet{};
        memcpy(&buffer, &packet, sizeof(length));
        
        std::cout << packet.duration << std::endl;
    }
}

void websocket_manager::websocket_init(const int &websocket_port, const std::string websocket_host)
{
    ix::initNetSystem();

    ix::WebSocketServer server(websocket_port, websocket_host);

    server.setOnClientMessageCallback([this](std::shared_ptr<ix::ConnectionState> connection_state, ix::WebSocket &webSocket, const ix::WebSocketMessagePtr &msg)
                                      {
        if(msg->type == ix::WebSocketMessageType::Message)
        {
            std::cout << "Remote ip: " << connection_state->getRemoteIp() << "\n" << "Payload: " << msg->str << std::endl;

        if(msg->binary)
        {
            binary_haptic_packet(webSocket, reinterpret_cast<const uint8_t*>(msg->str.data()), sizeof(msg->str));
        }
        else if(!msg->str.empty())
        {
            try
        {
            json websocket_message = json::parse(msg->str);

            if(websocket_message.contains("action") && websocket_message["action"] == "check file")
            {
                if(websocket_message.contains("id") && websocket_message["id"].is_array())
                {
                    std::vector<std::string> incoming_files;

                    incoming_files = websocket_message["id"].get<std::vector<std::string>>();

                    storage_manager manager;
                    std::vector<std::string> processed_files = manager.get_missing_files(incoming_files);
                    if(processed_files.empty())
                    {
                        this->valid_files(webSocket);
                    }
                    else
                    {
                        this->request_file(webSocket, processed_files);
                    }
                }
            }
        }
        catch(const json::parse_error& error)
        {
            std::cerr << "Parsing failed: " << error.what() << std::endl;
        }
        catch(const std::exception& error)
        {
            std::cerr << "Unexpected error: " << error.what() << std::endl;
        }
        }
        } });

    auto res = server.listen();
    if (!res.first)
    {
        return;
    }

    server.disablePerMessageDeflate();
    server.start();
    server.wait();
}

/*

*/