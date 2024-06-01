#include "link.h"
#include "node.h"
#include <iostream>

void Link::receive(Packet *packet, Node *fromNode) {
    std::string PacketId = packet->toString();
    std::string fromNodeId = fromNode->toString();
    Node *otherNode = other(fromNode);

    log("packet in: " + PacketId + " from " + fromNodeId);
    Simulator::schedule(Simulator::now() + this->delay(), [this, packet, otherNode]() {        
        this->send(packet, otherNode);
    });
}

void Link::send(Packet *packet, Node *otherNode) {
    std::string PacketId = packet->toString();
    std::string otherNodeId = otherNode->toString();

    log("packet out: " + PacketId + " to " + otherNodeId);
    otherNode->send(packet);
}