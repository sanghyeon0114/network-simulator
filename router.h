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
  int indexDestRoute(Address dest);

  virtual std::string name() override { return "Router"; }
  void log(std::string message) { Node::log(message); }
public:
  virtual void send(Packet *packet) override;
};

#endif