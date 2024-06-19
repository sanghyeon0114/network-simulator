#include "address.h"
#include "host.h"
#include "link.h"
#include <set>
#include <vector>

struct NatEntry {
  Address internalAddress;
  short internalPort;
  short externalPort;
};

class Nat : public Node {
private:
  Address address_;

  Link *wanLink_;
  std::vector<NatEntry> natTable_;

  static short nextPort_;

  virtual std::string name() override { return "Nat"; }
  Packet* convertExternalToInternalPacket(Packet* packet, Address InternalAddress, short InternalPort);
  Packet* convertInternalToExternalPacket(Packet* packet, short ExternalPort);
  Link* getProperLink(Packet* packet);
public:
  Nat(Address address) : address_(address) {}
  void setWanLink(Link *link) { wanLink_ = link; }
  virtual void send(Packet* packet, Link* link = nullptr) override;

  static short getNewPort();
};