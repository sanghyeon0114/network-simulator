#include "nat.h"

// Todo
/*
1. 밖으로 나갈 때,
패킷의 출발지 정보을 internalAddress와 internalPort를 비교하고
internalAddress(출발지 IP) -> Nat의 address_
internalPort(출발지 Port) -> externalPort

2. 안으로 들어올 때
패킷의 도착지 정보를 externalPort 비교하고
Nat의 address_(목적지 IP) -> internalAddress
externalPort(목적지 Port) -> internalPort
그리고 linkTable의 others들 중에 올바른 Node로 전송.
*/ 

short Nat::nextPort_ = 10000;

int Nat::getNewPort() {
    return Nat::nextPort_++;
}

void Nat::send(Packet* packet, Link* link) {

}