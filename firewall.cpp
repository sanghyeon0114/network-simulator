#include "firewall.h"
#include "host.h"

bool Firewall::AllowAnyPolicy::isAllowed(Packet* packet) {
    return this->destPort_ == packet->destPort();
}

bool Firewall::AllowSpecificPolicy::isAllowed(Packet* packet) {
    return this->srcAddress_ == packet->srcAddress() && this->destPort_ == packet->destPort();
}

Firewall::~Firewall() {
    for(FirewallPolicy* fp: policy_) {
        delete fp;
    }
}

void Firewall::addAllowAnyPolicy(short destPort) {
    AllowAnyPolicy* aap = new AllowAnyPolicy(destPort);
    policy_.push_back(aap);
}

void Firewall::addAllowSpecificPolicy(Address srcAddress, short destPort) {
    AllowSpecificPolicy* asp = new AllowSpecificPolicy(srcAddress, destPort);
    policy_.push_back(asp);
}

bool Firewall::isAllowPacket(Packet *packet) {
    for(FirewallPolicy* p: policy_) {
        if(p->isAllowed(packet)) {
            return true;
        }
    }
    return false;
}

Link* Firewall::getProperLink(Packet* packet) {
    for(Link* l: linkTable()) {
        if(Host* host = dynamic_cast<Host*>(l->other(this))) {
            if(host->address() == packet->destAddress()) {
                return l;
            }
        }
    }
    return nullptr;
}

void Firewall::send(Packet *packet, Link* link) {
    std::string packetInfo = packet->toString();
    std::string srcAddress = packet->srcAddress().toString();
    short destPort = packet->destPort();
    if(link == nullptr) {
        log("Dropping " + packetInfo + " with src address " + srcAddress + " and dest port " + std::to_string(destPort));
        delete packet;
        return;
    }
    
    if(link != receiveLink_) {
        receiveLink_->receive(packet, this);
        return;
    }
    if(isAllowPacket(packet)) {
        Link* pl = getProperLink(packet);
        if(pl == nullptr) {
            log("Dropping " + packetInfo + " with src address " + srcAddress + " and dest port " + std::to_string(destPort));
            delete packet;
            return;
        }
        pl->receive(packet, this);
        return;
    } else {
        log("Dropping " + packetInfo + " with src address " + srcAddress + " and dest port " + std::to_string(destPort));
        delete packet;
    }
}