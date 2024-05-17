#include "Node.h"


Node::Node(int id) : id_(id) {}

int Node::getId() const {
    return id_;
}

void Node::setId(int id) {
    id_ = id;
}

double Node::getLongitude() const {
    return longitude_;
}

void Node::setLongitude(double longitude) {
    longitude_ = longitude;
}

double Node::getLatitude() const {
    return latitude_;
}

void Node::setLatitude(double latitude) {
    latitude_ = latitude;
}

bool Node::operator==(const Node &rhs) const {
    return id_ == rhs.id_;
}