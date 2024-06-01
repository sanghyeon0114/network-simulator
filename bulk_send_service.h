#ifndef BULK_SEND_SERVICE_H
#define BULK_SEND_SERVICE_H

#include "host.h"
#include "service.h"
#include "simulator.h"

#define PACKET_SIZE 512

class BulkSendService : Service {
  friend class BulkSendServiceInstaller;

private:
  BulkSendService(Host *host, Address destAddress, short port,
                  double delay = 1, double startTime = 0,
                  double stopTime = 10.0);
  void send(Host *host, Address destAddress, short destPort);
  virtual void service(Packet* packet) override;
  virtual std::string name() override { return "BulkSendService"; }
  void log(std::string message) { Service::log(message); }
};

#endif