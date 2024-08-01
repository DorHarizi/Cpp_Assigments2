#pragma once

#include "node.hpp"
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <sstream>

/**
 * @class Tree
 * @brief Represents a k-ary tree.
 * @tparam T The type of the value stored in the nodes.
 * @tparam K The maximum number of children each node can have.
 */
template<typename T, int K = 2>
class Tree {
private:
    std::shared_ptr<Node<T>> root;  ///< The root node of the tree.

public:
    Tree() : root(nullptr) {}

    /**
     * @brief Add a root node to the tree.
     * @param node The node to set as the root.
     */
    void add_root(const Node<T>& node) {
        root = std::make_shared<Node<T>>(node);
    }

    /**
     * @brief Add a child node to a parent node.
     * @param parent_node The parent node to add the child to.
     * @param child_node The child node to add.
     */
    void add_sub_node(const Node<T>& parent_node, const Node<T>& child_node) {
        auto parent = find_node(root, parent_node.value);
        if (parent && parent->children.size() < K) {
            parent->add_child(std::make_shared<Node<T>>(child_node));
        }
    }

    /**
     * @brief Find a node with a specific value.
     * @param current The current node to search from.
     * @param value The value to search for.
     * @return The node with the specified value, or nullptr if not found.
     */
    std::shared_ptr<Node<T>> find_node(std::shared_ptr<Node<T>> current, const T& value) {
        if (!current) return nullptr;
        if (current->value == value) return current;
        for (auto& child : current->children) {
            auto result = find_node(child, value);
            if (result) return result;
        }
        return nullptr;
    }

    // Pre-order iterator
    class PreOrderIterator {
    private:
        std::stack<std::shared_ptr<Node<T>>> stack;

    public:
        PreOrderIterator(std::shared_ptr<Node<T>> root) {
            if (root) stack.push(root);
        }

        bool operator!=(const PreOrderIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const PreOrderIterator& other) const {
            return stack == other.stack;
        }

        PreOrderIterator& operator++() {
            if (stack.empty()) return *this;
            auto node = stack.top();
            stack.pop();
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                stack.push(*it);
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *stack.top();
        }

        Node<T>* operator->() const {
            return stack.top().get();
        }
    };

    PreOrderIterator begin_pre_order() {
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order() {
        return PreOrderIterator(nullptr);
    }

    // Post-order iterator
    class PostOrderIterator {
    private:
        std::stack<std::shared_ptr<Node<T>>> stack;
        std::stack<std::shared_ptr<Node<T>>> out;

    public:
        PostOrderIterator(std::shared_ptr<Node<T>> root) {
            if (root) {
                stack.push(root);
                while (!stack.empty()) {
                    auto node = stack.top();
                    stack.pop();
                    out.push(node);
                    for (auto& child : node->children) {
                        stack.push(child);
                    }
                }
            }
        }

        bool operator!=(const PostOrderIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const PostOrderIterator& other) const {
            return out == other.out;
        }

        PostOrderIterator& operator++() {
            if (!out.empty()) {
                out.pop();
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *out.top();
        }

        Node<T>* operator->() const {
            return out.top().get();
        }
    };

    PostOrderIterator begin_post_order() {
        return PostOrderIterator(root);
    }

    PostOrderIterator end_post_order() {
        return PostOrderIterator(nullptr);
    }

    // In-order iterator (specific to binary tree)
    class InOrderIterator {
    private:
        std::stack<std::shared_ptr<Node<T>>> stack;
        std::shared_ptr<Node<T>> current;

    public:
        InOrderIterator(std::shared_ptr<Node<T>> root) : current(root) {
            while (current) {
                stack.push(current);
                current = current->children.empty() ? nullptr : current->children[0];
            }
        }

        bool operator!=(const InOrderIterator& other) const {
            return current != other.current || stack != other.stack;
        }

        bool operator==(const InOrderIterator& other) const {
            return !(*this != other);
        }

        InOrderIterator& operator++() {
            if (stack.empty()) {
                current = nullptr;
                return *this;
            }

            current = stack.top();
            stack.pop();
            auto right_child = (current->children.size() > 1) ? current->children[1] : nullptr;
            current = right_child;

            while (current) {
                stack.push(current);
                current = current->children.empty() ? nullptr : current->children[0];
            }

            return *this;
        }

        Node<T>& operator*() const {
            return *stack.top();
        }

        Node<T>* operator->() const {
            return stack.top().get();
        }
    };

    InOrderIterator begin_in_order() {
        return InOrderIterator(root);
    }

    InOrderIterator end_in_order() {
        return InOrderIterator(nullptr);
    }

    // BFS iterator
    class BFSIterator {
    private:
        std::queue<std::shared_ptr<Node<T>>> queue;

    public:
        BFSIterator(std::shared_ptr<Node<T>> root) {
            if (root) queue.push(root);
        }

        bool operator!=(const BFSIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const BFSIterator& other) const {
            return queue == other.queue;
        }

        BFSIterator& operator++() {
            if (!queue.empty()) {
                auto node = queue.front();
                queue.pop();
                for (auto& child : node->children) {
                    queue.push(child);
                }
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *queue.front();
        }

        Node<T>* operator->() const {
            return queue.front().get();
        }
    };

    BFSIterator begin_bfs_scan() {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() {
        return BFSIterator(nullptr);
    }

    // DFS iterator
    class DFSIterator {
    private:
        std::stack<std::shared_ptr<Node<T>>> stack;

    public:
        DFSIterator(std::shared_ptr<Node<T>> root) {
            if (root) stack.push(root);
        }

        bool operator!=(const DFSIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const DFSIterator& other) const {
            return stack == other.stack;
        }

        DFSIterator& operator++() {
            if (!stack.empty()) {
                auto node = stack.top();
                stack.pop();
                for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                    stack.push(*it);
                }
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *stack.top();
        }

        Node<T>* operator->() const {
            return stack.top().get();
        }
    };

    DFSIterator begin_dfs_scan() {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan() {
        return DFSIterator(nullptr);
    }

    // Heapify method to convert binary tree to a min-heap
    void myHeap() {
        if (K != 2) return;
        std::vector<T> elements;
        for (auto it = begin_bfs_scan(); it != end_bfs_scan(); ++it) {
            elements.push_back(it->get_value());
        }
        std::sort(elements.begin(), elements.end());

        auto it = elements.begin();
        for (auto it_bfs = begin_bfs_scan(); it_bfs != end_bfs_scan(); ++it_bfs, ++it) {
            it_bfs->value = *it;
        }
    }

    // Destructor to clear the tree
    ~Tree() {
        root.reset();
    }

    // Printing method using some GUI library
    friend std::ostream& operator<<(std::ostream& os, const Tree<T, K>& tree) {
        os << tree.to_string();
        return os;
    }

    /**
     * @brief Convert the tree to a string representation.
     * @return The string representation of the tree.
     */
    std::string to_string() const {
        std::ostringstream oss;
        if (root) {
            print_tree(oss, root, 0);
        }
        return oss.str();
    }

    /**
     * @brief Recursively print the tree to an output stream.
     * @param oss The output stream.
     * @param node The current node to print.
     * @param depth The depth of the current node.
     */
    void print_tree(std::ostringstream& oss, std::shared_ptr<Node<T>> node, int depth) const {
        for (int i = 0; i < depth; ++i) {
            oss << "  ";
        }
        oss << node->get_value() << "\n";
        for (auto& child : node->children) {
            print_tree(oss, child, depth + 1);
        }
    }
};
