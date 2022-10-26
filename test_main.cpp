#include "avl_tree.cpp"

// Forked from https://raw.githubusercontent.com/komiamiko/allthealgos/master/avl_tree/avl_tree.cpp

#include <iostream>
int main() {
  // c++ version
  std::cout << __cplusplus << std::endl;
  // test node instantiation
  // (300)
  avl::avl_node<int, int, int> *node =
      new avl::avl_node<int, int, int>(300, 300);
  std::cout << avl::avl_node_size(node) << " (expected 1)" << std::endl;
  // test some insertion by index
  // (100 300)
  node = avl::avl_node_insert_at_index(
             node, 0, 100, avl::no_merge<int>(), avl::identity<int>(),
             std::plus<int>(), std::allocator<avl::avl_node<int, int, int>>())
             .first;
  std::cout << avl::avl_node_size(node) << " (expected 2)" << std::endl;
  // test some insertion ordered
  // (100 100 300)
  node = std::get<0>(avl::avl_node_insert_ordered(
      node, 100, std::less<int>(), avl::no_merge<int>(), avl::identity<int>(),
      std::plus<int>(), std::allocator<avl::avl_node<int, int, int>>()));
  std::cout << avl::avl_node_size(node) << " (expected 3)" << std::endl;
  // test some removal
  // (100 300)
  node = std::get<0>(avl::avl_node_remove_at_index(
      node, 1, avl::identity<int>(), std::plus<int>(),
      std::allocator<avl::avl_node<int, int, int>>()));
  std::cout << avl::avl_node_size(node) << " (expected 2)" << std::endl;
  // test some removal ordered
  // (100)
  node = std::get<0>(avl::avl_node_remove_ordered(
      node, 300, std::less<int>(), avl::identity<int>(), std::plus<int>(),
      std::allocator<avl::avl_node<int, int, int>>()));
  std::cout << avl::avl_node_size(node) << " (expected 1)" << std::endl;
  // test some element get
  // (100)
  std::cout << avl::avl_node_get_at_index(node, 0) << " (expected 100)" << std::endl;
  // test some element replace by index
  // (150)
  node = std::get<0>(avl::avl_node_replace_at_index(
      node, 0, 150, avl::no_merge<int>(), avl::identity<int>(),
      std::plus<int>(), std::allocator<avl::avl_node<int, int, int>>()
      ));
  std::cout << avl::avl_node_get_at_index(node, 0) << " (expected 150)" << std::endl;
  std::cout << avl::avl_node_size(node) << " (expected 1)" << std::endl;
  // test some element replace ordered
  // (150)
  node = std::get<0>(avl::avl_node_replace_ordered(
      node, 250, 350, std::less<int>(), avl::no_merge<int>(), avl::identity<int>(),
      std::plus<int>(), std::allocator<avl::avl_node<int, int, int>>()
      ));
  std::cout << avl::avl_node_get_at_index(node, 0) << " (expected 150)" << std::endl;
  std::cout << avl::avl_node_size(node) << " (expected 1)" << std::endl;
  node = std::get<0>(avl::avl_node_replace_ordered(
      node, 150, 350, std::less<int>(), avl::no_merge<int>(), avl::identity<int>(),
      std::plus<int>(), std::allocator<avl::avl_node<int, int, int>>()
      ));
  std::cout << avl::avl_node_get_at_index(node, 0) << " (expected 350)" << std::endl;
  std::cout << avl::avl_node_size(node) << " (expected 1)" << std::endl;
  // test making a tree
  avl::avl_tree<int> tree;
  std::cout << tree.size() << " (expected 0)" << std::endl;
  tree.insert(0, 11);
  tree.insert(0, 22);
  tree.insert(0, 33);
  tree.insert(0, 44);
  std::cout << tree.size() << " (expected 4)" << std::endl;
  avl::avl_tree<int> tree2 = tree;
  std::cout << tree2.size() << " (expected 4)" << std::endl;
}
