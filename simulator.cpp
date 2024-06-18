#include "simulator.h"
#include "object.h"

double Simulator::time_ = 0.0;
std::priority_queue<Schedule> Simulator::events;

void Simulator::run() {
  Object::initializeAll();

  for (; !Simulator::events.empty(); Simulator::events.pop()) {
      Schedule s = Simulator::events.top();
      time_ = s.time();
      s.call();
    }

  Object::cleanup();
}