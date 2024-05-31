#include "router.h"
#include <iostream>

int Router::indexDestRoute(Address dest) {
    for(size_t i = 0; i < routingTable_.size(); i++) {
        if(routingTable_[i].destination == dest) {
            return i;
        }
    }
    return -1;
}

void Router::send(Packet *packet) {
    std::string from = packet->srcAddress().toString();
    std::string to = packet->destAddress().toString();
    std::string dataLength = std::to_string(packet->dataString().size());

    int routingTableIndex = Router::indexDestRoute(packet->destAddress());
    if(routingTableIndex == -1) {
        std::cout << "Router #" << id() << ": no route for packet (from: " << from << ", to: " << to << ", " << dataLength << " bytes)" << std::endl;
        delete packet;
        return;
    }

    std::cout << "Router #" << id() << ": forwarding packet (from: " << from << ", to: " << to << ", " << dataLength << " bytes)" << std::endl;
    routingTable_[routingTableIndex].nextLink->send(packet, this);
}