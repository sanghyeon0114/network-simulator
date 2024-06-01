#ifndef PACKET_SINK_SERVICE_H
#define PACKET_SINK_SERVICE_H

#include "service.h"
#include <string>

class PacketSinkService : public Service {
  friend class PacketSinkServiceInstaller;
private:
  int totalPacketSize;
  PacketSinkService(Host *host, short port): Service(host, port) { totalPacketSize = 0; }
  virtual void service(Packet* packet) override;
  virtual std::string name() override { return "PacketSinkService"; }
  void log(std::string message) { Service::log(message); }
};

#endif