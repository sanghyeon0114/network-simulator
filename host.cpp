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

    if(address_ == packet->srcAddress()) {
        std::cout << "Host #" << id() << ": sending packet (from: " << from << ", to: " << to << ", " << dataLength << " bytes)" << std::endl;

        size_t linkTableSize = linkTable().size();
        linkTable()[rand() % linkTableSize]->send(packet, this);
    } else if(address_ == packet->destAddress()) {
        Service* service = Host::getService(packet->destPort());
        std::cout << "Host #" << id() << ": received packet, destination port: " << packet->destPort() << std::endl;
        if(service == nullptr) {
            std::cout << "Host #" << id() << ": no service for packet (from: " << from << ", to: " << to << ", " << dataLength << " bytes)" << std::endl;
            delete packet;
            return;
        }
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