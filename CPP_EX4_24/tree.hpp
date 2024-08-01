#pragma once

#include "node.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <iostream>

/**
 * @brief A class to represent a k-ary tree.
 * 
 * @tparam T Type of the data stored in the tree nodes.
 * @tparam K Maximum number of children per node (default is 2).
 */
template <typename T, int K = 2>
class Tree {
private:
    Node<T>* root;  ///< Root node of the tree.

public:
    /**
     * @brief Constructor to initialize a k-ary tree.
     */
    Tree() : root(nullptr) {}
    
    /**
     * @brief Adds a root node to the tree.
     * @param node Node to be set as the root.
     */
    void add_root(Node<T>& node) {
        if (root != nullptr) delete_tree(root);
        root = new Node<T>(node.data);
    }

    /**
     * @brief Adds a child node to a given parent node.
     * @param parent_node Parent node to add the child to.
     * @param child_node Child node to add.
     * @return True if the child node was added successfully, false otherwise.
     */
    bool add_sub_node(Node<T>& parent_node, Node<T>& child_node) {
        Node<T>* parent = find(root, parent_node.data);
        if (parent == nullptr || parent->children.size() >= K) return false;
        parent->children.push_back(new Node<T>(child_node.data));
        return true;
    }

    /**
     * @brief Finds a node with a given value in the tree.
     * @param node Starting node for the search.
     * @param value Value to search for.
     * @return Pointer to the node if found, nullptr otherwise.
     */
    Node<T>* find(Node<T>* node, T value) {
        if (node == nullptr) return nullptr;
        if (node->data == value) return node;
        for (Node<T>* child : node->children) {
            Node<T>* result = find(child, value);
            if (result != nullptr) return result;
        }
        return nullptr;
    }

    // Implement iterators here

    class PreOrderIterator {
    private:
        Node<T>* current;
        std::stack<Node<T>*> stack;
    public:
        PreOrderIterator(Node<T>* root) {
            if (root) stack.push(root);
            current = nullptr;
        }

        bool operator!=(const PreOrderIterator& other) const {
            return !stack.empty();
        }

        PreOrderIterator& operator++() {
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
                for (int i = current->children.size() - 1; i >= 0; --i) {
                    stack.push(current->children[i]);
                }
            } else {
                current = nullptr;
            }
            return *this;
        }

        Node<T>* operator*() {
            return current;
        }
    };

    class PostOrderIterator {
    private:
        Node<T>* current;
        std::stack<Node<T>*> stack;
        std::stack<Node<T>*> visit_stack;

        void init_stack(Node<T>* root) {
            if (root) {
                stack.push(root);
                while (!stack.empty()) {
                    Node<T>* node = stack.top();
                    stack.pop();
                    visit_stack.push(node);
                    for (Node<T>* child : node->children) {
                        stack.push(child);
                    }
                }
            }
        }

    public:
        PostOrderIterator(Node<T>* root) {
            init_stack(root);
            current = nullptr;
        }

        bool operator!=(const PostOrderIterator& other) const {
            return !visit_stack.empty();
        }

        PostOrderIterator& operator++() {
            if (!visit_stack.empty()) {
                current = visit_stack.top();
                visit_stack.pop();
            } else {
                current = nullptr;
            }
            return *this;
        }

        Node<T>* operator*() {
            return current;
        }
    };

    class InOrderIterator {
    private:
        Node<T>* current;
        std::stack<Node<T>*> stack;

        void init_stack(Node<T>* root) {
            while (root) {
                stack.push(root);
                root = root->children.empty() ? nullptr : root->children[0];
            }
        }

    public:
        InOrderIterator(Node<T>* root) {
            init_stack(root);
            current = nullptr;
        }

        bool operator!=(const InOrderIterator& other) const {
            return !stack.empty();
        }

        InOrderIterator& operator++() {
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
                Node<T>* right_child = current->children.size() > 1 ? current->children[1] : nullptr;
                if (right_child) init_stack(right_child);
            } else {
                current = nullptr;
            }
            return *this;
        }

        Node<T>* operator*() {
            return current;
        }
    };

    class BFSIterator {
    private:
        Node<T>* current;
        std::queue<Node<T>*> queue;
    public:
        BFSIterator(Node<T>* root) {
            if (root) queue.push(root);
            current = nullptr;
        }

        bool operator!=(const BFSIterator& other) const {
            return !queue.empty();
        }

        BFSIterator& operator++() {
            if (!queue.empty()) {
                current = queue.front();
                queue.pop();
                for (Node<T>* child : current->children) {
                    queue.push(child);
                }
            } else {
                current = nullptr;
            }
            return *this;
        }

        Node<T>* operator*() {
            return current;
        }
    };

    class DFSIterator {
    private:
        Node<T>* current;
        std::stack<Node<T>*> stack;
    public:
        DFSIterator(Node<T>* root) {
            if (root) stack.push(root);
            current = nullptr;
        }

        bool operator!=(const DFSIterator& other) const {
            return !stack.empty();
        }

        DFSIterator& operator++() {
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
                for (int i = current->children.size() - 1; i >= 0; --i) {
                    stack.push(current->children[i]);
                }
            } else {
                current = nullptr;
            }
            return *this;
        }

        Node<T>* operator*() {
            return current;
        }
    };

    // Methods to get iterators
    PreOrderIterator begin_pre_order() {
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order() {
        return PreOrderIterator(nullptr);
    }

    PostOrderIterator begin_post_order() {
        return PostOrderIterator(root);
    }

    PostOrderIterator end_post_order() {
        return PostOrderIterator(nullptr);
    }

    InOrderIterator begin_in_order() {
        return InOrderIterator(root);
    }

    InOrderIterator end_in_order() {
        return InOrderIterator(nullptr);
    }

    BFSIterator begin_bfs_scan() {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() {
        return BFSIterator(nullptr);
    }

    DFSIterator begin_dfs_scan() {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan() {
        return DFSIterator(nullptr);
    }

    /**
     * @brief Destructor to delete the entire tree and free memory.
     */
    ~Tree() { delete_tree(root); }
    
    /**
     * @brief Deletes all nodes in the tree recursively.
     * @param node Starting node for deletion.
     */
    void delete_tree(Node<T>* node) {
        if (node == nullptr) return;
        for (Node<T>* child : node->children) {
            delete_tree(child);
        }
        delete node;
    }

    /**
     * @brief Gets the root node of the tree.
     * @return Pointer to the root node.
     */
    Node<T>* get_root() const {
        return root;
    }
};

// Overload << operator to print the tree using GUI
template <typename T, int K>
std::ostream& operator<<(std::ostream& os, const Tree<T, K>& tree) {
    // This function should be implemented to interface with the GUI
    return os;
}
