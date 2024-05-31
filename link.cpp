#include "link.h"
#include "node.h"
#include <iostream>

void Link::send(Packet *packet, Node *fromNode) {
    Node *otherNode = other(fromNode);
    std::string PacketId = packet->toString();
    std::string fromNodeId = fromNode->toString();
    std::string otherNodeId = otherNode->toString();

    log("packet in: " + PacketId + " from " + fromNodeId);
    log("packet out: " + PacketId + " to " + otherNodeId);
    otherNode->send(packet);
}