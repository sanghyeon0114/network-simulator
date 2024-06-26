#ifndef HOST_H
#define HOST_H

#include "address.h"
#include "packet.h"
#include "service.h"
#include <vector>

class Host : public Node {
  friend class ServiceInstaller;

private:
  // 호스트의 주소
  Address address_;

  // 설치된 서비스 목록
  std::vector<Service *> services_;
  virtual std::string name() override { return "Host"; }
  void log(std::string message) { Node::log(message); }
public:
  Address address() { return address_; }
  Host(Address address) : address_(address) {}
  ~Host();
  
  // 호스트와 설치된 서비스를 전부 초기화한다.
  virtual void initialize() override;

  // 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
  virtual void send(Packet *packet,  Link* link = nullptr) override;
  Service* getService(short port);
  int nextServicePort();
};

#endif