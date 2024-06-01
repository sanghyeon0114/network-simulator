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
    int distance_;
    Node *node_;
    Link *link_;

    Distance(int distance, Node *node, Link *link) : distance_(distance), node_(node), link_(link) {}

    bool operator<(const Distance &s) const {
        return this->distance_ > s.distance_;
    }
};

class AutoRouter : public Router {
private:
    virtual std::string name() override { return "AutoRouter"; }
public:
void calculate(const std::vector<Node *> &nodes, const std::vector<Link *> &links) {
    int size = nodes.size();
    
    std::map<int, int> distance;
    std::map<int, Link *> getLink;
    std::map<int, Node *> getNode;

    // distance, getNode, getLink 해시맵 초기화
    for(int i = 0; i < size; i++) {
        distance[nodes[i]->id()] = INT_MAX;
        getLink[nodes[i]->id()] = nullptr;
        getNode[nodes[i]->id()] = nodes[i];
    }
    
    distance[this->id()] = 0;
    std::priority_queue<Distance> pq;

    for (Link* link : this->linkTable()) {
            pq.push(Distance(link->delay(), link->other(this), link));
        }

    while(!pq.empty()) {
        Distance tmp = pq.top();
        pq.pop();
        int tmpDistance = tmp.distance_;
        Node* tmpNode = tmp.node_;
        Link* tmpLink = tmp.link_;

        if(distance[tmpNode->id()] <= tmpDistance) {
            continue;
        }

        distance[tmpNode->id()] = tmpDistance;
        getLink[tmpNode->id()] = tmpLink;

        for(Link* link : tmpNode->linkTable()) {
            Node *other = link->other(tmpNode);
            int otherDistance = tmpDistance + link->delay();
            if(distance[other->id()] > otherDistance) {
                pq.push(Distance(otherDistance, other, tmpLink));
            }
        }
    }

    routingTable_.clear();
    for(auto iter: distance) {
        int id = iter.first;
        Node *node = getNode[id];
        Link *link = getLink[id];

        if(link != nullptr) {
            if(Host *host = dynamic_cast<Host *>(node)) {
                RoutingEntry routingEntry = {host->address(), link};
                this->routingTable_.push_back(routingEntry);
            }
        }
    }
}
};

#endif