#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include <iostream>

struct RoutingEntry {
public:
  Address destination;
  Link *nextLink;
};

class Router : public Node {
protected:
  std::vector<RoutingEntry> routingTable_;
private:
  virtual std::string name() override { return "Router"; }
  int indexDestRoute(Address dest);
public:
  virtual void send(Packet *packet) override;
};

#endif