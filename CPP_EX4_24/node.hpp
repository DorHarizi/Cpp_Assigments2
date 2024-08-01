#pragma once

#include <vector>

/**
 * @brief A class to represent a node in the k-ary tree.
 * 
 * @tparam T Type of the data stored in the node.
 */
template <typename T>
class Node {
public:
    T data;  ///< Data stored in the node.
    std::vector<Node<T>*> children;  ///< Children of the node.

    /**
     * @brief Constructor to initialize a node with given value.
     * @param value Data to be stored in the node.
     */
    Node(T value) : data(value) {}

    /**
     * @brief Gets the value stored in the node.
     * @return Value of the node.
     */
    T get_value() const {
        return data;
    }
};