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

void Firewall::send(Packet *packet, Link* link) {
    if(link == nullptr) {
        delete packet;
        return;
    }
    
    if(link != receiveLink_) {
        receiveLink_->send(packet, this);
        return;
    }
    if(isAllowPacket(packet)) {
        for(Link* l: linkTable()) {
            if(Host* host = dynamic_cast<Host*>(l->other(this))) {
                if(host->address() == packet->destAddress()) {
                    l->receive(packet, this);
                    return;
                }
            }
        }
    } else {
        delete packet;
    }
};