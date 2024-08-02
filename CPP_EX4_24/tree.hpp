#pragma once

#include "node.hpp"
#include <vector>
#include <stack>
#include <queue>
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

        /**
         * @brief Helper function to delete a tree recursively.
         * @param node Root node of the tree/subtree to delete.
         */
        void delete_tree(Node<T>* node) {
            if (node == nullptr) return;
            for (Node<T>* child : node->children) {
                delete_tree(child);
            }
            delete node;
        }

        /**
         * @brief Helper function to print the tree recursively.
         * @param node Current node to print.
         * @param depth Current depth in the tree (used for indentation).
         */
        void print_tree(Node<T>* node, int depth) const {
            if (node == nullptr) return;
            for (int i = 0; i < depth; ++i) {
                std::cout << "  ";  // Indentation for the current depth
            }
            std::cout << node->data << std::endl;
            for (Node<T>* child : node->children) {
                print_tree(child, depth + 1);
            }
        }

    public:
        /**
         * @brief Constructor to initialize a k-ary tree.
         */
        Tree() : root(nullptr) {}

        /**
         * @brief Destructor to clean up the tree.
         */
        ~Tree() {
            delete_tree(root);
        }

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

        /**
         * @brief Prints the tree to the standard output.
         */
        void print() const {
            print_tree(root, 0);
        }

        class PreOrderIterator {
            private:
                std::stack<Node<T>*> stack;

            public:
                PreOrderIterator(Node<T>* root) {
                    if (root) stack.push(root);
                }

                bool operator!=(const PreOrderIterator& other) const {
                    return !stack.empty() || !other.stack.empty();
                }

                PreOrderIterator& operator++() {
                    if (!stack.empty()) {
                        Node<T>* current = stack.top();
                        stack.pop();
                        for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                            stack.push(*it);
                        }
                    }
                    return *this;
                }

                Node<T>& operator*() {
                    return *stack.top();
                }

                Node<T>* operator->() {
                    return stack.top();
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
                        if (!visit_stack.empty()) {
                            current = visit_stack.top();
                            visit_stack.pop();
                        } else {
                            current = nullptr;
                        }
                    }
                }

            public:
                PostOrderIterator(Node<T>* root) : current(nullptr) {
                    init_stack(root);
                }

                bool operator!=(const PostOrderIterator& other) const {
                    return current != other.current;
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

                Node<T>& operator*() {
                    return *current;
                }

                Node<T>* operator->() {
                    return current;
                }
        };

        class InOrderIterator {
            private:
                Node<T>* current;
                std::stack<Node<T>*> stack;

                void init_stack(Node<T>* node) {
                    while (node != nullptr) {
                        stack.push(node);
                        node = node->children.empty() ? nullptr : node->children[0];
                    }
                }

            public:
                InOrderIterator(Node<T>* root) : current(nullptr) {
                    init_stack(root);
                    if (!stack.empty()) {
                        current = stack.top();
                        stack.pop();
                    }
                }

                bool operator!=(const InOrderIterator& other) const {
                    return current != other.current;
                }

                InOrderIterator& operator++() {
                    if (current != nullptr) {
                        Node<T>* node = current->children.size() > 1 ? current->children[1] : nullptr;
                        if (node) {
                            init_stack(node);
                        }
                        if (!stack.empty()) {
                            current = stack.top();
                            stack.pop();
                        } else {
                            current = nullptr;
                        }
                    }
                    return *this;
                }

                Node<T>& operator*() {
                    return *current;
                }

                Node<T>* operator->() {
                    return current;
                }
        };

        class BFSIterator {
            private:
                Node<T>* current;
                std::queue<Node<T>*> queue;
                
            public:
                BFSIterator(Node<T>* root) : current(nullptr) {
                    if (root) {
                        queue.push(root);
                        current = queue.front();
                    }
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
                        if (queue.empty()) {
                            current = nullptr;
                        } else {
                            current = queue.front();
                        }
                    } else {
                        current = nullptr;
                    }
                    return *this;
                }

                Node<T>& operator*() {
                    return *current;
                }

                Node<T>* operator->() {
                    return current;
                }
        };

        class DFSIterator {
            private:
                Node<T>* current;
                std::stack<Node<T>*> stack;
                
            public:
                DFSIterator(Node<T>* root) : current(root) {
                    if (root) {
                        stack.push(root);
                    }
                }

                bool operator!=(const DFSIterator& other) const {
                    return current != other.current;
                }

                DFSIterator& operator++() {
                    if (!stack.empty()) {
                        current = stack.top();
                        stack.pop();
                        for (std::size_t i = current->children.size(); i > 0; --i) {
                            stack.push(current->children[i - 1]);
                        }
                    } else {
                        current = nullptr;
                    }
                    return *this;
                }

                Node<T>& operator*() {
                    return *current;
                }

                Node<T>* operator->() {
                    return current;
                }
        };


        // Methods to get Pre-Order Iterator
        PreOrderIterator begin_pre_order() {
            return PreOrderIterator(root);
        }

        PreOrderIterator end_pre_order() {
            return PreOrderIterator(nullptr);
        }

        // Methods to get Post-Order Iterator
        PostOrderIterator begin_post_order() {
            return PostOrderIterator(root);
        }

        PostOrderIterator end_post_order() {
            return PostOrderIterator(nullptr);
        }

        // Methods to get In-Order Iterator
        InOrderIterator begin_in_order() {
            return InOrderIterator(root);
        }

        InOrderIterator end_in_order() {
            return InOrderIterator(nullptr);
        }

        // Methods to get BFS Iterator
        BFSIterator begin_bfs_scan() {
            return BFSIterator(root);
        }

        BFSIterator end_bfs_scan() {
            return BFSIterator(nullptr);
        }

        // Methods to get DFS Iterator
        DFSIterator begin_dfs_scan() {
            return DFSIterator(root);
        }

        DFSIterator end_dfs_scan() {
            return DFSIterator(nullptr);
        }

        // Default begin and end methods
        BFSIterator begin() {
            return BFSIterator(root);
        }

        BFSIterator end() {
            return BFSIterator(nullptr);
        }
};
