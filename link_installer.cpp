#include "link_installer.h"

Link *LinkInstaller::install(Node *a, Node *b) {
    Link* link = new Link(a, b);
    a->linkTable_.push_back(link);
    b->linkTable_.push_back(link);
    return link;
}