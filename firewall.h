#include "address.h"
#include "node.h"
#include "object.h"
#include <set>
#include <string>

class FirewallPolicy : public Object {};

class Firewall : public Node {
private:
  class AllowAnyPolicy : public FirewallPolicy {
  private:
    short destPort_;
    virtual std::string name() override { return "AllowAnyPolicy"; };
  public:
    AllowAnyPolicy(short destPort) : destPort_(destPort) {}
    bool getDestPort() { return destPort_; }
  };

  class AllowSpecificPolicy : public FirewallPolicy {
  private:
    Address srcAddress_;
    short destPort_;
    virtual std::string name() override { return "AllowSpecificPolicy"; };
  public:
    AllowSpecificPolicy(Address srcAddress, short destPort)
        : srcAddress_(srcAddress), destPort_(destPort) {}
    bool getDestPort() { return destPort_; }
  };

  Link *receiveLink_ = nullptr;

  virtual std::string name() override { return "Firewall"; }
public:
  void setReceiveLink(Link *link) { receiveLink_ = link; }

  void addAllowAnyPolicy(short destPort);
  void addAllowSpecificPolicy(Address srcAddress, short destPort);
  virtual void send(Packet *packet) override;
};