#include "host.h"
#include <iostream>
#include <random>
#include <string>

Host::~Host() {
    for(size_t i = 0; i < services_.size(); i++) {
        delete services_[i];
    }
    services_.clear();
}

void Host::initialize() {
    // not need
}

void Host::send(Packet *packet) {
    std::string from = packet->srcAddress().toString();
    std::string to = packet->destAddress().toString();
    std::string dataLength = std::to_string(packet->dataString().size());
    std::string packetId = packet->toString();

    if(address_ == packet->srcAddress()) {
        log("sending packet: " + packetId);

        size_t linkTableSize = linkTable().size();
        linkTable()[rand() % linkTableSize]->receive(packet, this);
    } else if(address_ == packet->destAddress()) {
        Service* service = Host::getService(packet->destPort());
        if(service == nullptr) {
            log("no service for packet: " + packetId);
            delete packet;
            return;
        }
        log("received packet: " + packetId + ", forwarding to " + service->toString());
        service->service(packet);
    }
    
}

Service* Host::getService(short port) {
    for(size_t i = 0; i < services_.size(); i++) {
        if(services_[i]->getPort() == port) {
            return services_[i];
        }
    }
    return nullptr;
}

int Host::nextServicePort() {
    return 1000 + services_.size();
}