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
    std::string packetId = packet->toString();

    int routingTableIndex = Router::indexDestRoute(packet->destAddress());
    if(routingTableIndex == -1) {
        log("no route for packet: " + packetId);
        delete packet;
        return;
    }
    Link *nextLink = routingTable_[routingTableIndex].nextLink;
    std::string linkId = nextLink->toString();
    log("forwarding packet: " + packetId + " to " + linkId);
    nextLink->receive(packet, this);
}