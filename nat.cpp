#include "nat.h"

short Nat::nextPort_ = 10000;

short Nat::getNewPort() {
    return Nat::nextPort_++;
}

Packet* Nat::convertExternalToInternalPacket(Packet* packet, Address InternalAddress, short InternalPort) {
    Packet* newPacket = new Packet(packet->srcAddress(), InternalAddress, packet->srcPort(), InternalPort, packet->data());
    delete packet;
    return newPacket;
}

Packet* Nat::convertInternalToExternalPacket(Packet* packet, short ExternalPort) {
    Packet* newPacket = new Packet(address_, packet->destAddress(), ExternalPort, packet->destPort(), packet->data());
    delete packet;
    return newPacket;
}

Link* Nat::getProperLink(Packet* packet) {
    for(Link* l: linkTable()) {
        if(Host* host = dynamic_cast<Host*>(l->other(this))) {
            if(host->address() == packet->destAddress()) {
                return l;
            }
        }
    }
    return nullptr;
}

void Nat::send(Packet* packet, Link* link) {
    std::string packetInfo = packet->toString();
    std::string srcAddress = packet->srcAddress().toString();
    short destPort = packet->destPort();
    
    if(link == wanLink_) { 
        for(NatEntry ne: natTable_) {
            if(packet->destAddress() == address_ && packet->destPort() == ne.externalPort) {
                Packet* newPacket = convertExternalToInternalPacket(packet, ne.internalAddress, ne.internalPort);
                Link* pl = getProperLink(newPacket);
                if(pl == nullptr) {
                    log("Dropping " + packetInfo + " with src address " + srcAddress + " and dest port " + std::to_string(destPort));
                    delete packet;
                    return;
                }
                pl->receive(newPacket, this);
                return;
            }
        }
        log("Dropping " + packetInfo + " with src address " + srcAddress + " and dest port " + std::to_string(destPort));
        delete packet;
    } else {
        short ExternalPort = -1;
        for(NatEntry ne: natTable_) {
            if(packet->srcAddress() == ne.internalAddress && packet->srcPort() == ne.internalPort) {
                ExternalPort = ne.externalPort;
                break;
            }
        }
        if(ExternalPort == -1) {
            NatEntry newNatEntry = {packet->srcAddress(), packet->srcPort(), getNewPort()};
            natTable_.push_back(newNatEntry);
            ExternalPort = newNatEntry.externalPort;
        }
        Packet* newPacket = convertInternalToExternalPacket(packet, ExternalPort);
        wanLink_->receive(newPacket, this);
    }
}