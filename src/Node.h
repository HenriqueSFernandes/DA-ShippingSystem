//
// Created by memechanic on 04-05-2024.
//

#ifndef SHIPPING_SYSTEM_NODE_H
#define SHIPPING_SYSTEM_NODE_H


class Node {
public:

    Node(int id);

    [[nodiscard]] int getId() const;

    void setId(int id);

    [[nodiscard]] double getLongitude() const;

    void setLongitude(double longitude);

    [[nodiscard]] double getLatitude() const;

    void setLatitude(double latitude);

    bool operator==(const Node &rhs) const;

private:
    int id_;
    double longitude_;
    double latitude_;
};


#endif //SHIPPING_SYSTEM_NODE_H
