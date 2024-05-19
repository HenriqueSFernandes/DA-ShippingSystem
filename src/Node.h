/// @file Node.h
#ifndef SHIPPING_SYSTEM_NODE_H
#define SHIPPING_SYSTEM_NODE_H

/**
 * @class Node
 * @brief This class represents a node of the graph.
 *
 * Each node has an id, longitude, and latitude. The id is unique for each node.
 * The longitude and latitude represent the geographical coordinates of the node.
 */
class Node {
public:

    /**
     * @brief Constructor.
     * @param id The id of the node.
     */
    explicit Node(int id);

    /**
     * @brief Id getter.
     * @return The id of the node.
     */
    [[nodiscard]] int getId() const;

    /**
     * @brief Id setter.
     * @param id The new id of the node.
     */
    void setId(int id);

    /**
     * @brief Longitude getter.
     * @return The longitude of the node.
     */
    [[nodiscard]] double getLongitude() const;

    /**
     * @brief Longitude setter.
     * @param longitude The new longitude of the node.
     */
    void setLongitude(double longitude);

    /**
     * @brief Latitude getter.
     * @return The latitude of the node.
     */
    [[nodiscard]] double getLatitude() const;

    /**
     * @brief Latitude setter.
     * @param latitude The new latitude of the node.
     */
    void setLatitude(double latitude);

    /**
     * @brief Equality operator overload.
     * @param rhs The node to compare to.
     * @return True if the id of the 2 nodes match, false otherwise.
     */
    bool operator==(const Node &rhs) const;

private:
    int id_;
    double longitude_;
    double latitude_;
};


#endif //SHIPPING_SYSTEM_NODE_H
