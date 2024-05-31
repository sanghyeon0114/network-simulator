#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "object.h"
#include "packet.h"
#include <vector>

class Node : Object {
  friend class LinkInstaller;

private:
  int id_;
  static int nextId_;

  std::vector<Link *> linkTable_;
public:
  Node() : id_(nextId_++) {}
  int id() const { return id_; }
  std::vector<Link *> linkTable() { return linkTable_; }
  virtual ~Node() {};
  virtual void send(Packet* packet) = 0;
  std::string toString() { return Object::toString(); }

protected:
  void log(std::string message) { Object::log(message); }
};

#endif