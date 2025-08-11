#include "cangatewayclient.h"
#include "json.hpp" // Make sure nlohmann/json.hpp is available

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

using json = nlohmann::json;
const char* SOCKET_PATH = "/tmp/mysocket";

CanGatewayClient::CanGatewayClient(QObject *parent) : QObject(parent) {}

void CanGatewayClient::process() {
    int client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_socket == -1) {
        emit errorOccurred("Failed to create socket.");
        emit finished();
        return;
    }

    sockaddr_un server_addr;
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    if (::connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        emit errorOccurred("Failed to connect to the server.");
        close(client_socket);
        emit finished();
        return;
    }

    std::cout << "✅ C++ Client: Connected to the CAN gateway server." << std::endl;

    char buffer[4096];
    std::string stream_buffer;

    while (true) {
        ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);

        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            stream_buffer.append(buffer);

            size_t pos;
            while ((pos = stream_buffer.find('\n')) != std::string::npos) {
                std::string json_string = stream_buffer.substr(0, pos);
                stream_buffer.erase(0, pos + 1);

                try {
                    json can_data = json::parse(json_string);
                    
                    QVariantList dataList;
                    for (const auto& item : can_data["data"]) {
                        dataList.append(item.get<int>());
                    }
                    
                    // Instead of printing, emit a signal with the data!
                    emit messageReceived(can_data["id"], can_data["dlc"], dataList, can_data["timestamp"]);

                } catch (json::parse_error& e) {
                    emit errorOccurred(QString("JSON Parse Error: %1").arg(e.what()));
                }
            }
        } else {
            // Server disconnected or error
            emit errorOccurred("Server disconnected or read error.");
            break;
        }
    }

    close(client_socket);
    emit finished();
}