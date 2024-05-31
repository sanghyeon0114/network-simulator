#include "link.h"
#include "node.h"
#include <iostream>

void Link::send(Packet *packet, Node *fromNode) {
    Node *otherNode = other(fromNode);
    std::string from = std::to_string(fromNode->id());
    std::string to = std::to_string(otherNode->id());
    std::cout << "Link: forwarding packet from node #" << from << ", to node #" << to << std::endl;

    otherNode->send(packet);
}