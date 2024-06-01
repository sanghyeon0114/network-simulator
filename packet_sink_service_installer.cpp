#include "packet_sink_service_installer.h"

PacketSinkService *PacketSinkServiceInstaller::install(Host *host, short port) {
    PacketSinkService* packetSinkService = new PacketSinkService(host, port);
    ServiceInstaller::install(host, packetSinkService);
    return packetSinkService;
}