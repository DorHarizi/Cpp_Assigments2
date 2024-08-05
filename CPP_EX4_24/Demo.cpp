#include <iostream>
#include "node.hpp"
#include "tree.hpp"


int main() {
    Node<double> root_node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    std::cout << std::endl;
    std::cout << "The print with the Pre-order Iterator: " << std::endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        std::cout << node->get_value() << std::endl;
    } 
    // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    std::cout << std::endl;
    std::cout << "The print with the Post-order Iterator: " << std::endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        std::cout << node->get_value() << std::endl;
    } 
    // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    std::cout << std::endl;
    std::cout << "The print with the In-order Iterator: " << std::endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        std::cout << node->get_value() << std::endl;
    } 
    // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    std::cout << std::endl;
    std::cout << "The print with the BFS Iterator: " << std::endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        std::cout << node->get_value() << std::endl;
    } 
    // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    std::cout << std::endl;
    std::cout << "The print with the DFS Iterator: " << std::endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        std::cout << node->get_value() << std::endl;
    } 
    // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    std::cout << std::endl;
    std::cout << "The print with the Tree Order (default BFS): " << std::endl;
    for (auto node : tree) {
        std::cout << node.get_value() << std::endl;
    } 
    // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    std::cout << std::endl;
    std::cout << "The print with the MinHeap Iterator: " << std::endl;
    for (auto node = tree.begin_min_heap(); node != tree.end_min_heap(); ++node) {
        std::cout << node->get_value() << std::endl;
    } 
    // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    Tree<double, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    // The tree should look like:
    // /**
    //  *       root = 1.1
    //  *     /      |     \
    //  *    1.2    1.3    1.4
    //  *   /        |
    //  *  1.5      1.6
    //  */

    std::cout << std::endl;
    std::cout << "The print with the Pre-order Iterator for Three-Ary Tree: " << std::endl;
    for (auto node = three_ary_tree.begin_pre_order_non_binary(); node != three_ary_tree.end_pre_order_non_binary(); ++node) {
        std::cout << node->get_value() << std::endl;
    } 
    // prints: 1.1, 1.2, 1.5, 1.3, 1.6, 1.4

    std::cout << std::endl;
    std::cout << "The print with the Post-order Iterator for Three-Ary Tree: " << std::endl;
    for (auto node = three_ary_tree.begin_post_order_non_binary(); node != three_ary_tree.end_post_order_non_binary(); ++node) {
        std::cout << node->get_value() << std::endl;
    } 
    // prints: 1.5, 1.2, 1.6, 1.3, 1.4, 1.1

    std::cout << std::endl;
    std::cout << "The print with the In-order Iterator for Three-Ary Tree: " << std::endl;
    for (auto node = three_ary_tree.begin_in_order_non_binary(); node != three_ary_tree.end_in_order_non_binary(); ++node) {
        std::cout << node->get_value() << std::endl;
    } 
    // prints: 1.5, 1.2, 1.1, 1.6, 1.3, 1.4

    std::cout << std::endl;
    std::cout << "The print with the BFS Iterator for Three-Ary Tree: " << std::endl;
    for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node) {
        std::cout << node->get_value() << std::endl;
    } 
    // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    std::cout << std::endl;
    std::cout << "The print with the DFS Iterator for Three-Ary Tree: " << std::endl;
    for (auto node = three_ary_tree.begin_dfs_scan(); node != three_ary_tree.end_dfs_scan(); ++node) {
        std::cout << node->get_value() << std::endl;
    } 
    // prints: 1.1, 1.2, 1.5, 1.3, 1.6, 1.4

    std::cout << std::endl;
    std::cout << "The print with the Tree Order (default BFS) for Three-Ary Tree: " << std::endl;
    for (auto node : three_ary_tree) {
        std::cout << node.get_value() << std::endl;
    } 
    // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    std::cout << std::endl;
    std::cout << "The print with the MinHeap Iterator for Three-Ary Tree: " << std::endl;
    for (auto node = three_ary_tree.begin_min_heap(); node != three_ary_tree.end_min_heap(); ++node) {
        std::cout << node->get_value() << std::endl;
    } 
    // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    Complex c3(5.0, 6.0);
    Complex c4(7.0, 8.0);

    // Create nodes with complex numbers
    Node<Complex> node1(c1);
    Node<Complex> node2(c2);
    Node<Complex> node3(c3);
    Node<Complex> node4(c4);

    // Create the tree and add nodes
    Tree<Complex> tree1;
    tree1.add_root(node1);
    tree1.add_sub_node(node1, node2);
    tree1.add_sub_node(node1, node3);
    tree1.add_sub_node(node2, node4);

    // Traverse the tree1
    std::cout << std::endl;
    std::cout << "The print for tree1 Tree: " << std::endl;
    for (auto node : tree1) {
        Complex tmp = node.get_value();
        std::cout << tmp.to_string() << std::endl;
    } 
    // prints: 1+2i, 3+4i, 5+6i, 7+8i

    // cout << tree; // Should print the graph using GUI.
    // cout << three_ary_tree; // Should print the graph using GUI.


    return 0;
}
