#include "bulk_send_service.h"

BulkSendService::BulkSendService(Host *host, Address destAddress, short port, double delay, double startTime, double stopTime): Service(host, port) {}

void BulkSendService::send(Host *host, Address destAddress, short destPort) {
    std::string data = "";
    for(int i = 0; i < 128; i++) {
        data.append("AAAA");
    }

    log("sending data");
    Packet* newPacket = new Packet(host->address(), destAddress, port_, destPort, data);
    host->send(newPacket);
}

void BulkSendService::service(Packet* packet) {
    // no need.
}