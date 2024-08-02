#pragma once

#include "node.hpp"
#include <vector>
#include <stack>
#include <queue>
#include <iostream>

/**
 * @brief A class to represent a k-ary tree.
 * 
 * A k-ary tree where each node can have up to K children. Provides various methods
 * for managing and traversing the tree, including iterators for different traversal orders.
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
         * 
         * Recursively deletes all nodes in the subtree rooted at the given node.
         * 
         * @param node Root node of the subtree to delete.
         */
        void delete_tree(Node<T>* node) {
            if (node == nullptr) return;  ///< Base case: empty node.
            for (Node<T>* child : node->children) {
                delete_tree(child);  ///< Recursively delete each child.
            }
            delete node;  ///< Delete the current node.
        }

    public:
        /**
         * @brief Constructor to initialize a k-ary tree.
         * 
         * Initializes an empty tree with no root.
         */
        Tree() : root(nullptr) {}

        /**
         * @brief Destructor to clean up the tree.
         * 
         * Calls the helper function to recursively delete all nodes in the tree.
         */
        ~Tree() {
            delete_tree(root);
        }

        /**
         * @brief Adds a root node to the tree.
         * 
         * Sets the provided node as the new root of the tree, deleting the old root if it exists.
         * 
         * @param node Node to be set as the root.
         */
        void add_root(Node<T>& node) {
            if (root != nullptr) delete_tree(root);  ///< Delete old root if exists.
            root = new Node<T>(node.data);  ///< Set new root.
        }

        /**
         * @brief Adds a child node to a given parent node.
         * 
         * Finds the parent node in the tree and adds the child node if the parent exists and has room for more children.
         * 
         * @param parent_node Parent node to add the child to.
         * @param child_node Child node to add.
         * @return True if the child node was added successfully, false otherwise.
         */
        bool add_sub_node(Node<T>& parent_node, Node<T>& child_node) {
            Node<T>* parent = find(root, parent_node.data);  ///< Find the parent node.
            if (parent == nullptr || parent->children.size() >= K) return false;  ///< Check if parent exists and can have more children.
            parent->children.push_back(new Node<T>(child_node.data));  ///< Add the child node.
            return true;
        }

        /**
         * @brief Finds a node with a given value in the tree.
         * 
         * Searches for a node with the specified value starting from the given node.
         * 
         * @param node Starting node for the search.
         * @param value Value to search for.
         * @return Pointer to the node if found, nullptr otherwise.
         */
        Node<T>* find(Node<T>* node, T value) {
            if (node == nullptr) return nullptr;  ///< Base case: empty node.
            if (node->data == value) return node;  ///< Node found.
            for (Node<T>* child : node->children) {
                Node<T>* result = find(child, value);  ///< Recursively search in children.
                if (result != nullptr) return result;  ///< Node found in children.
            }
            return nullptr;  ///< Node not found.
        }

        /**
         * @brief Iterator for pre-order traversal of the tree.
         * 
         * Traverses nodes in a pre-order fashion: visit node, then recursively visit children.
         */
        class PreOrderIterator {
            private:
                std::stack<Node<T>*> stack;  ///< Stack to keep track of nodes during traversal.

            public:
                /**
                 * @brief Constructor for PreOrderIterator.
                 * 
                 * Initializes the iterator for pre-order traversal from the root node.
                 * 
                 * @param root Starting node for the traversal.
                 */
                PreOrderIterator(Node<T>* root) {
                    if (root) stack.push(root);  ///< Push the root node onto the stack.
                }

                /**
                 * @brief Comparison operator to check if two iterators are different.
                 * 
                 * Iterators are considered different if either has nodes left to visit.
                 * 
                 * @param other The other iterator to compare with.
                 * @return True if the iterators are different, false otherwise.
                 */
                bool operator!=(const PreOrderIterator& other) const {
                    return !stack.empty() || !other.stack.empty();
                }

                /**
                 * @brief Increment operator to move to the next node.
                 * 
                 * Moves to the next node in pre-order traversal by popping the stack and pushing children.
                 * 
                 * @return Reference to the current iterator.
                 */
                PreOrderIterator& operator++() {
                    if (!stack.empty()) {
                        Node<T>* current = stack.top();  ///< Get the current node.
                        stack.pop();  ///< Remove the current node from the stack.
                        for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                            stack.push(*it);  ///< Push children onto the stack in reverse order.
                        }
                    }
                    return *this;
                }

                /**
                 * @brief Dereference operator to access the current node.
                 * 
                 * @return Reference to the current node.
                 */
                Node<T>& operator*() {
                    return *stack.top();
                }

                /**
                 * @brief Arrow operator to access the current node's members.
                 * 
                 * @return Pointer to the current node.
                 */
                Node<T>* operator->() {
                    return stack.top();
                }
        };

        /**
         * @brief Iterator for post-order traversal of the tree.
         * 
         * Traverses nodes in a post-order fashion: recursively visit children, then visit node.
         */
        class PostOrderIterator {
            private:
                Node<T>* current;  ///< Current node being accessed.
                std::stack<Node<T>*> stack;  ///< Stack to help with traversal.
                std::stack<Node<T>*> visit_stack;  ///< Stack to keep nodes for post-order.

                /**
                 * @brief Initializes the visit_stack for post-order traversal.
                 * 
                 * Populates visit_stack with nodes in post-order by processing all children first.
                 * 
                 * @param root The root node to start the initialization.
                 */
                void init_stack(Node<T>* root) {
                    if (root) {
                        stack.push(root);  ///< Start with the root node.
                        while (!stack.empty()) {
                            Node<T>* node = stack.top();  ///< Get the top node.
                            stack.pop();  ///< Remove the top node from the stack.
                            visit_stack.push(node);  ///< Add it to visit_stack.
                            for (Node<T>* child : node->children) {
                                stack.push(child);  ///< Add children to the stack.
                            }
                        }
                        if (!visit_stack.empty()) {
                            current = visit_stack.top();  ///< Set the current node.
                            visit_stack.pop();  ///< Remove it from visit_stack.
                        } else {
                            current = nullptr;  ///< No more nodes to visit.
                        }
                    }
                }

            public:
                /**
                 * @brief Constructor for PostOrderIterator.
                 * 
                 * Initializes the iterator for post-order traversal from the root node.
                 * 
                 * @param root Starting node for the traversal.
                 */
                PostOrderIterator(Node<T>* root) : current(nullptr) {
                    init_stack(root);  ///< Initialize stacks for traversal.
                }

                /**
                 * @brief Comparison operator to check if two iterators are different.
                 * 
                 * Iterators are considered different if they have different current nodes.
                 * 
                 * @param other The other iterator to compare with.
                 * @return True if the iterators are different, false otherwise.
                 */
                bool operator!=(const PostOrderIterator& other) const {
                    return current != other.current;
                }

                /**
                 * @brief Increment operator to move to the next node.
                 * 
                 * Moves to the next node in post-order traversal by updating the current node.
                 * 
                 * @return Reference to the current iterator.
                 */
                PostOrderIterator& operator++() {
                    if (!visit_stack.empty()) {
                        current = visit_stack.top();  ///< Get the current node.
                        visit_stack.pop();  ///< Remove it from visit_stack.
                    } else {
                        current = nullptr;  ///< No more nodes to visit.
                    }
                    return *this;
                }

                /**
                 * @brief Dereference operator to access the current node.
                 * 
                 * @return Reference to the current node.
                 */
                Node<T>& operator*() {
                    return *current;
                }

                /**
                 * @brief Arrow operator to access the current node's members.
                 * 
                 * @return Pointer to the current node.
                 */
                Node<T>* operator->() {
                    return current;
                }
        };

        /**
         * @brief Iterator for in-order traversal of the tree.
         * 
         * Traverses nodes in an in-order fashion: visit leftmost child, then node, then rightmost child.
         */
        class InOrderIterator {
            private:
                Node<T>* current;  ///< Current node being accessed.
                std::stack<Node<T>*> stack;  ///< Stack to help with traversal.

                /**
                 * @brief Initializes the stack for in-order traversal.
                 * 
                 * Pushes nodes onto the stack until reaching the leftmost node.
                 * 
                 * @param node The starting node for the initialization.
                 */
                void init_stack(Node<T>* node) {
                    while (node != nullptr) {
                        stack.push(node);  ///< Add node to the stack.
                        node = node->children.empty() ? nullptr : node->children[0];  ///< Move to the leftmost child.
                    }
                }

            public:
                /**
                 * @brief Constructor for InOrderIterator.
                 * 
                 * Initializes the iterator for in-order traversal from the root node.
                 * 
                 * @param root Starting node for the traversal.
                 */
                InOrderIterator(Node<T>* root) : current(nullptr) {
                    init_stack(root);  ///< Initialize the stack for traversal.
                    if (!stack.empty()) {
                        current = stack.top();  ///< Set the current node.
                        stack.pop();  ///< Remove it from the stack.
                    }
                }

                /**
                 * @brief Comparison operator to check if two iterators are different.
                 * 
                 * Iterators are considered different if they have different current nodes.
                 * 
                 * @param other The other iterator to compare with.
                 * @return True if the iterators are different, false otherwise.
                 */
                bool operator!=(const InOrderIterator& other) const {
                    return current != other.current;
                }

                /**
                 * @brief Increment operator to move to the next node.
                 * 
                 * Moves to the next node in in-order traversal by updating the current node.
                 * 
                 * @return Reference to the current iterator.
                 */
                InOrderIterator& operator++() {
                    if (current != nullptr) {
                        Node<T>* node = current->children.size() > 1 ? current->children[1] : nullptr;  ///< Get the right child.
                        if (node) {
                            init_stack(node);  ///< Initialize stack with right child's subtree.
                        }
                        if (!stack.empty()) {
                            current = stack.top();  ///< Set the current node.
                            stack.pop();  ///< Remove it from the stack.
                        } else {
                            current = nullptr;  ///< No more nodes to visit.
                        }
                    }
                    return *this;
                }

                /**
                 * @brief Dereference operator to access the current node.
                 * 
                 * @return Reference to the current node.
                 */
                Node<T>& operator*() {
                    return *current;
                }

                /**
                 * @brief Arrow operator to access the current node's members.
                 * 
                 * @return Pointer to the current node.
                 */
                Node<T>* operator->() {
                    return current;
                }
        };

        /**
         * @brief Iterator for breadth-first search (BFS) traversal of the tree.
         * 
         * Traverses nodes level by level from the root down to the leaves.
         */
        class BFSIterator {
            private:
                Node<T>* current;  ///< Current node being accessed.
                std::queue<Node<T>*> queue;  ///< Queue to help with traversal.
                
            public:
                /**
                 * @brief Constructor for BFSIterator.
                 * 
                 * Initializes the iterator for BFS traversal from the root node.
                 * 
                 * @param root Starting node for the traversal.
                 */
                BFSIterator(Node<T>* root) : current(nullptr) {
                    if (root) {
                        queue.push(root);  ///< Start with the root node.
                        current = queue.front();  ///< Set the current node.
                    }
                }

                /**
                 * @brief Comparison operator to check if two iterators are different.
                 * 
                 * Iterators are considered different if they have different states.
                 * 
                 * @param other The other iterator to compare with.
                 * @return True if the iterators are different, false otherwise.
                 */
                bool operator!=(const BFSIterator& other) const {
                    return !queue.empty();
                }

                /**
                 * @brief Increment operator to move to the next node.
                 * 
                 * Moves to the next node in BFS traversal by updating the current node.
                 * 
                 * @return Reference to the current iterator.
                 */
                BFSIterator& operator++() {
                    if (!queue.empty()) {
                        current = queue.front();  ///< Get the current node.
                        queue.pop();  ///< Remove it from the queue.
                        for (Node<T>* child : current->children) {
                            queue.push(child);  ///< Add children to the queue.
                        }
                        if (queue.empty()) {
                            current = nullptr;  ///< No more nodes to visit.
                        } else {
                            current = queue.front();  ///< Set the current node.
                        }
                    } else {
                        current = nullptr;  ///< No more nodes to visit.
                    }
                    return *this;
                }

                /**
                 * @brief Dereference operator to access the current node.
                 * 
                 * @return Reference to the current node.
                 */
                Node<T>& operator*() {
                    return *current;
                }

                /**
                 * @brief Arrow operator to access the current node's members.
                 * 
                 * @return Pointer to the current node.
                 */
                Node<T>* operator->() {
                    return current;
                }
        };

        /**
         * @brief Iterator for depth-first search (DFS) traversal of the tree.
         * 
         * Traverses nodes by going deep into each branch before moving to the next sibling.
         */
        class DFSIterator {
            private:
                Node<T>* current;  ///< Current node being accessed.
                std::stack<Node<T>*> stack;  ///< Stack to help with traversal.
                
            public:
                /**
                 * @brief Constructor for DFSIterator.
                 * 
                 * Initializes the iterator for DFS traversal from the root node.
                 * 
                 * @param root Starting node for the traversal.
                 */
                DFSIterator(Node<T>* root) : current(root) {
                    if (root) {
                        stack.push(root);  ///< Start with the root node.
                    }
                }

                /**
                 * @brief Comparison operator to check if two iterators are different.
                 * 
                 * Iterators are considered different if they have different current nodes.
                 * 
                 * @param other The other iterator to compare with.
                 * @return True if the iterators are different, false otherwise.
                 */
                bool operator!=(const DFSIterator& other) const {
                    return current != other.current;
                }

                /**
                 * @brief Increment operator to move to the next node.
                 * 
                 * Moves to the next node in DFS traversal by updating the current node.
                 * 
                 * @return Reference to the current iterator.
                 */
                DFSIterator& operator++() {
                    if (!stack.empty()) {
                        current = stack.top();  ///< Get the current node.
                        stack.pop();  ///< Remove it from the stack.
                        for (std::size_t i = current->children.size(); i > 0; --i) {
                            stack.push(current->children[i - 1]);  ///< Push children onto the stack.
                        }
                    } else {
                        current = nullptr;  ///< No more nodes to visit.
                    }
                    return *this;
                }

                /**
                 * @brief Dereference operator to access the current node.
                 * 
                 * @return Reference to the current node.
                 */
                Node<T>& operator*() {
                    return *current;
                }

                /**
                 * @brief Arrow operator to access the current node's members.
                 * 
                 * @return Pointer to the current node.
                 */
                Node<T>* operator->() {
                    return current;
                }
        };

        // Methods to get Pre-Order Iterator

        /**
         * @brief Gets an iterator for pre-order traversal of the tree.
         * 
         * @return An iterator for pre-order traversal starting from the root.
         */
        PreOrderIterator begin_pre_order() {
            return PreOrderIterator(root);
        }

        /**
         * @brief Gets an iterator representing the end of the pre-order traversal.
         * 
         * @return An iterator representing the end of pre-order traversal.
         */
        PreOrderIterator end_pre_order() {
            return PreOrderIterator(nullptr);
        }

        /**
         * @brief Gets an iterator for pre-order traversal of the tree for non-binary case.
         * 
         * @return An iterator for DFS traversal starting from the root.
         */
        DFSIterator begin_pre_order_non_binary() {
            return DFSIterator(root);
        }

        /**
         * @brief Gets an iterator representing the end of the pre-order traversal for non-binary case.
         * 
         * @return An iterator representing the end of DFS traversal.
         */
        DFSIterator end_pre_order_non_binary() {
            return DFSIterator(nullptr);
        }

        // Methods to get Post-Order Iterator

        /**
         * @brief Gets an iterator for post-order traversal of the tree.
         * 
         * @return An iterator for post-order traversal starting from the root.
         */
        PostOrderIterator begin_post_order() {
            return PostOrderIterator(root);
        }

        /**
         * @brief Gets an iterator representing the end of the post-order traversal.
         * 
         * @return An iterator representing the end of post-order traversal.
         */
        PostOrderIterator end_post_order() {
            return PostOrderIterator(nullptr);
        }

        /**
         * @brief Gets an iterator for post-order traversal of the tree for non-binary case.
         * 
         * @return An iterator for DFS traversal starting from the root.
         */
        DFSIterator begin_post_order_non_binary() {
            return DFSIterator(root);
        }

        /**
         * @brief Gets an iterator representing the end of the post-order traversal for non-binary case.
         * 
         * @return An iterator representing the end of DFS traversal.
         */
        DFSIterator end_post_order_non_binary() {
            return DFSIterator(nullptr);
        }

        // Methods to get In-Order Iterator

        /**
         * @brief Gets an iterator for in-order traversal of the tree.
         * 
         * @return An iterator for in-order traversal starting from the root.
         */
        InOrderIterator begin_in_order() {
            return InOrderIterator(root);
        }

        /**
         * @brief Gets an iterator representing the end of the in-order traversal.
         * 
         * @return An iterator representing the end of in-order traversal.
         */
        InOrderIterator end_in_order() {
            return InOrderIterator(nullptr);
        }

        /**
         * @brief Gets an iterator for in-order traversal of the tree for non-binary case.
         * 
         * @return An iterator for DFS traversal starting from the root.
         */
        DFSIterator begin_in_order_non_binary() {
            return DFSIterator(root);
        }

        /**
         * @brief Gets an iterator representing the end of the in-order traversal for non-binary case.
         * 
         * @return An iterator representing the end of DFS traversal.
         */
        DFSIterator end_in_order_non_binary() {
            return DFSIterator(nullptr);
        }


        // Methods to get BFS Iterator

        /**
         * @brief Gets an iterator for breadth-first search (BFS) traversal of the tree.
         * 
         * @return An iterator for BFS traversal starting from the root.
         */
        BFSIterator begin_bfs_scan() {
            return BFSIterator(root);
        }

        /**
         * @brief Gets an iterator representing the end of the BFS traversal.
         * 
         * @return An iterator representing the end of BFS traversal.
         */
        BFSIterator end_bfs_scan() {
            return BFSIterator(nullptr);
        }

        // Methods to get DFS Iterator

        /**
         * @brief Gets an iterator for depth-first search (DFS) traversal of the tree.
         * 
         * @return An iterator for DFS traversal starting from the root.
         */
        DFSIterator begin_dfs_scan() {
            return DFSIterator(root);
        }

        /**
         * @brief Gets an iterator representing the end of the DFS traversal.
         * 
         * @return An iterator representing the end of DFS traversal.
         */
        DFSIterator end_dfs_scan() {
            return DFSIterator(nullptr);
        }

        // Default begin and end methods

        /**
         * @brief Gets an iterator for BFS traversal as the default iteration method.
         * 
         * @return An iterator for BFS traversal starting from the root.
         */
        BFSIterator begin() {
            return BFSIterator(root);
        }

        /**
         * @brief Gets an iterator representing the end of the default iteration method.
         * 
         * @return An iterator representing the end of BFS traversal.
         */
        BFSIterator end() {
            return BFSIterator(nullptr);
        }
};
