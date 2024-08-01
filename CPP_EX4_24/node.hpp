#pragma once

#include <vector>
#include <memory>

/**
 * @class Node
 * @brief Represents a node in a k-ary tree.
 * @tparam T The type of the value stored in the node.
 */
template<typename T>
class Node {
public:
    T value;  ///< The value stored in the node.
    std::vector<std::shared_ptr<Node<T>>> children;  ///< The children of the node.

    /**
     * @brief Constructor to initialize the node with a value.
     * @param val The value to initialize the node with.
     */
    Node(T val) : value(val) {}

    /**
     * @brief Get the value stored in the node.
     * @return The value of the node.
     */
    T get_value() const { return value; }

    /**
     * @brief Add a child node.
     * @param child The child node to add.
     */
    void add_child(std::shared_ptr<Node<T>> child) {
        children.push_back(child);
    }
};