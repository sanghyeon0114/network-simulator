#include "address.h"
#include "node.h"
#include "object.h"
#include <set>
#include <string>

class FirewallPolicy : public Object {
public:
  virtual bool isAllowed(Packet* packet) = 0;
};

class Firewall : public Node {
private:
  class AllowAnyPolicy : public FirewallPolicy {
  private:
    short destPort_;
    virtual std::string name() override { return "AllowAnyPolicy"; };
  public:
    AllowAnyPolicy(short destPort) : destPort_(destPort) {}
    virtual bool isAllowed(Packet* packet) override;
  };

  class AllowSpecificPolicy : public FirewallPolicy {
  private:
    Address srcAddress_;
    short destPort_;
    virtual std::string name() override { return "AllowSpecificPolicy"; };
  public:
    AllowSpecificPolicy(Address srcAddress, short destPort)
        : srcAddress_(srcAddress), destPort_(destPort) {}
    virtual bool isAllowed(Packet* packet) override;
  };

  Link *receiveLink_ = nullptr;
  std::vector<FirewallPolicy *> policy_;

  virtual std::string name() override { return "Firewall"; }
  ~Firewall();
  bool isAllowPacket(Packet *packet);
  Link* getProperLink(Packet* packet);
public:
  void setReceiveLink(Link *link) { receiveLink_ = link; }

  void addAllowAnyPolicy(short destPort);
  void addAllowSpecificPolicy(Address srcAddress, short destPort);
  virtual void send(Packet *packet, Link* link) override;
};