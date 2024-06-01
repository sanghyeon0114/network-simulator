#ifndef AUTO_ROUTER_H
#define AUTO_ROUTER_H

#include "host.h"
#include "link.h"
#include "router.h"
#include "service.h"
#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>

struct Distance {
    double delay_;
    Node *node_;
    Link *link_;

    Distance(double delay, Node *node, Link *link) : delay_(delay), node_(node), link_(link) {}

    bool operator<(const Distance &s) const {
        return this->delay_ > s.delay_;
    }
};

class AutoRouter : public Router {
private:
    virtual std::string name() override { return "AutoRouter"; }
public:
    void calculate(const std::vector<Node *> &nodes, const std::vector<Link *> &links) {
        std::map<Node*, double> delayMap;
        std::map<Node*, Link*> linkMap;
    
        for(auto& node: nodes) {
            delayMap[node] = std::numeric_limits<double>::infinity();
            linkMap[node] = nullptr;
        }

        delayMap[this] = 0.0;

        std::priority_queue<Distance> pq;

        for(auto& link: this->linkTable()) {
            Node* other = link->other(this);
            delayMap[other] = link->delay();
            linkMap[other] = link;
            pq.push(Distance(delayMap[other], other, linkMap[other]));
        }
    
        while(!pq.empty()) {
            Distance tmp = pq.top();
            pq.pop();

            for(auto& link: tmp.node_->linkTable()) {
                double totalDelay = tmp.delay_ + link->delay();
                Node* tmpLinkOther = link->other(tmp.node_);

                if(delayMap[tmpLinkOther] > totalDelay) {
                    delayMap[tmpLinkOther] = totalDelay;
                    linkMap[tmpLinkOther] = tmp.link_; // first link in shortest path.
                    pq.push(Distance(delayMap[tmpLinkOther], tmpLinkOther, linkMap[tmpLinkOther]));
                }   
            }
        }

        this->routingTable_.clear();
        for(auto& iter: linkMap) {
            Node* node = iter.first;
            Link* link = iter.second;
            if(link == nullptr || node == this) {
                continue;
            }
            if(Host* host = dynamic_cast<Host*>(node)) {
                this->routingTable_.push_back({host->address(), link});
            } 
        }
    }
};

#endif