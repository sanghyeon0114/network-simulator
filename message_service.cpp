#include "message_service.h"

void MessageService::send(std::string message) {
    Packet* packet = new Packet(host_->address(), destAddress_, port_, destPort_, message);
    host_->send(packet);
}

void MessageService::service(Packet* packet) {
    std::string fromAddress = packet->srcAddress().toString();
    std::string fromPort = std::to_string(packet->srcPort());
    std::string data = packet->dataString();

    std::cout << "MessageService: received \"" << data << "\" from " << fromAddress << ":" << fromPort << std::endl;
    delete packet;
}