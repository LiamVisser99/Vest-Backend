#include "network/websocket.hpp"

void websocket_manager::request_file(ix::WebSocket &websocket, const std::vector<std::string> &file_id)
{
    json request = {
        {"action", "get missing file"},
        {"id", file_id}};

    std::cout << "Payload sent: " << request << std::endl;
    websocket.send(std::move(request.dump()));
}

void websocket_manager::valid_files(ix::WebSocket &websocket)
{
    json request = {
        {"action", "all files valid"}};

    std::cout << "Payload sent: " << request << std::endl;
    websocket.send(std::move(request.dump()));
}

void websocket_manager::binary_haptic_packet(const uint8_t *buffer, size_t length)
{
    if (length == sizeof(haptic_packet))
    {
        haptic_packet packet{};
        memcpy(&buffer, &packet, sizeof(length));
    }
}

/*
void websocket::haptic_call(ix::WebSocket &websocket, const std::string& file_id)
{
    
}
*/

void websocket_manager::init(const int &websocket_port, const std::string websocket_host)
{
    std::cout << "Websocket started" << "\n";

    ix::initNetSystem();

    ix::WebSocketServer server(websocket_port, websocket_host);

    server.setOnClientMessageCallback([this](std::shared_ptr<ix::ConnectionState> connection_state, ix::WebSocket &websocket, const ix::WebSocketMessagePtr &msg)
                                      {
        if (msg->type == ix::WebSocketMessageType::Message)
        {
            std::cout << "Remote ip: " << connection_state->getRemoteIp() << "\n"
                      << "Payload: " << msg->str << std::endl;

            try
            {
                json websocket_message = json::parse(msg->str);

                
            }
            catch (const json::parse_error &error)
            {
                std::cerr << "Parsing failed: " << error.what() << std::endl;
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
  if (websocket_message.contains("action") && websocket_message["action"] == "check file")
                {
                    if (websocket_message.contains("id") && websocket_message["id"].is_array())
                    {
                        std::vector<std::string> incoming_files;

                        incoming_files = websocket_message["id"].get<std::vector<std::string>>();

                        storage_manager manager;
                        std::vector<std::string> processed_files = manager.get_missing_files(incoming_files);
                        if (processed_files.empty())
                        {
                            this->valid_files(websocket);
                        }
                        else
                        {
                            this->request_file(websocket, processed_files);
                        }
                    }
                }
*/