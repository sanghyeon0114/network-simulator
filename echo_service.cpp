#include "echo_service.h"

void EchoService::service(Packet* packet) {
    std::string fromAddress = packet->srcAddress().toString();
    std::string fromPort = std::to_string(packet->srcPort());
    std::string data = packet->dataString();
    std::string message = "received \"" + data + "\" from " + fromAddress + ":" + fromPort + ", send reply with same data";
    log(message);

    Packet* newPacket = new Packet(host_->address(), packet->srcAddress(), port_, packet->srcPort(), data);
    host_->send(newPacket);
    delete packet;
}