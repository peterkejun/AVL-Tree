#include "avl_tree.cpp"

// Forked from https://raw.githubusercontent.com/komiamiko/allthealgos/master/avl_tree/avl_tree.cpp

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

struct fstatistics_t {
  double min = 1e100;
  double max = -1e100;
  double sum = 0;
  int count = 0;
};

fstatistics_t operator + (const fstatistics_t& lhs, const fstatistics_t& rhs) {
  return fstatistics_t{fmin(lhs.min, rhs.min), fmax(lhs.max, rhs.max), lhs.sum + rhs.sum, lhs.count + rhs.count};
}

struct to_fstatistics_t {
  fstatistics_t operator() (const double& x) const {
    return fstatistics_t{x, x, x, 1};
  }
};

struct summarize_fstatistics_t {
  std::string operator() (const fstatistics_t& x) const {
    std::ostringstream oss;
    oss << x.min << ", " << (x.sum / x.count) << ", " << x.max;
    return oss.str();
  }
};

unsigned int ipow(unsigned int b, unsigned int p) {
  unsigned int result = 1;
  unsigned int pos = 1;
  while(pos) {
    if(pos & p) {
      result *= b;
    }
    pos <<= 1;
    b *= b;
  }
  return result;
}

struct rhash_t {
  unsigned int value = 0;
  unsigned int count = 0;
};

rhash_t operator + (const rhash_t& lhs, const rhash_t& rhs) {
  return rhash_t{lhs.value * ipow(3, rhs.count) + rhs.value, lhs.count + rhs.count};
}

struct to_rhash_t {
  rhash_t operator() (const char& v) const {
    return rhash_t{v, 1};
  }
};



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
  // test split at index 1
  std::cout << "AVL Split Testing" << std::endl;
  auto result = avl::avl_node_split(node, 1, avl::no_merge<int>(), avl::identity<int>(), std::plus<int>(), std::allocator<avl::avl_node<int, int, int>>());
  std::cout << avl::avl_node_size(std::get<0>(result)) << " (expected 1)" << std::endl;
  std::cout << avl::avl_node_size(std::get<1>(result)) << " (expected 2)" << std::endl;
  // test some insertion by index
  // (100 100 300)
  node = avl::avl_node_insert_at_index(
             node, 0, 100, avl::no_merge<int>(), avl::identity<int>(),
             std::plus<int>(), std::allocator<avl::avl_node<int, int, int>>())
             .first;
  std::cout << avl::avl_node_size(node) << " (expected 3)" << std::endl;
  
  // test some removal
  // (100 300)
  node = std::get<0>(avl::avl_node_remove_at_index(
      node, 1, avl::identity<int>(), std::plus<int>(),
      std::allocator<avl::avl_node<int, int, int>>()));
  std::cout << avl::avl_node_size(node) << " (expected 2)" << std::endl;
  std::cout << int(avl::avl_node_depth(node)) << " (expected 2)" << std::endl;
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
  std::cout << int(avl::avl_node_depth(node)) << " (expected 1)" << std::endl;
  node = std::get<0>(avl::avl_node_insert_ordered(
      node, 450, std::less<int>(), avl::no_merge<int>(), avl::identity<int>(),
      std::plus<int>(), std::allocator<avl::avl_node<int, int, int>>()));
  std::cout << int(avl::avl_node_depth(node)) << " (expected 2)" << std::endl;
  node = std::get<0>(avl::avl_node_insert_ordered(
      node, 550, std::less<int>(), avl::no_merge<int>(), avl::identity<int>(),
      std::plus<int>(), std::allocator<avl::avl_node<int, int, int>>()));
  std::cout << int(avl::avl_node_depth(node)) << " (expected 2)" << std::endl;
  node = std::get<0>(avl::avl_node_insert_ordered(
      node, 650, std::less<int>(), avl::no_merge<int>(), avl::identity<int>(),
      std::plus<int>(), std::allocator<avl::avl_node<int, int, int>>()));
  std::cout << int(avl::avl_node_depth(node)) << " (expected 3)" << std::endl;
  node = std::get<0>(avl::avl_node_insert_ordered(
      node, 660, std::less<int>(), avl::no_merge<int>(), avl::identity<int>(),
      std::plus<int>(), std::allocator<avl::avl_node<int, int, int>>()));
  node = std::get<0>(avl::avl_node_insert_ordered(
      node, 670, std::less<int>(), avl::no_merge<int>(), avl::identity<int>(),
      std::plus<int>(), std::allocator<avl::avl_node<int, int, int>>()));
  node = std::get<0>(avl::avl_node_insert_ordered(
      node, 680, std::less<int>(), avl::no_merge<int>(), avl::identity<int>(),
      std::plus<int>(), std::allocator<avl::avl_node<int, int, int>>()));
  std::cout << int(avl::avl_node_depth(node)) << " (expected 3)" << std::endl;
  node = std::get<0>(avl::avl_node_insert_ordered(
      node, 690, std::less<int>(), avl::no_merge<int>(), avl::identity<int>(),
      std::plus<int>(), std::allocator<avl::avl_node<int, int, int>>()));
  std::cout << int(avl::avl_node_depth(node)) << " (expected 4)" << std::endl;
  // test multiset usage
  avl::avl_node<std::pair<int, int>, int, avl::monostate>* msroot = nullptr;
  for(int i = 2; i < 10000; ++i) {
    int j = i;
    while(j > 1) {
      msroot = std::get<0>(avl::avl_node_insert_ordered(
        msroot, std::make_pair(j, 1), std::less<std::pair<int, int>>(),
        avl::merge_count<int, int>(), avl::monostate(), std::plus<avl::monostate>(), std::allocator<
          avl::avl_node<std::pair<int, int>, int, avl::monostate>>()));
      if(j&1) {j = 3*j+1;} else {j >>= 1;}
    }
  }
  std::cout << avl::avl_node_size(msroot) << " (expected 21663)" << std::endl;
  std::cout << avl::avl_node_get_at_index(msroot, 0).second << " (expected 9998)" << std::endl;
  std::cout << avl::avl_node_get_at_index(msroot, 21).second << " (expected 4483)" << std::endl;
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
  std::cout << tree2.get_item(0) << " (expected 44)" << std::endl;
  std::cout << tree2.get_item(1) << " (expected 33)" << std::endl;
  std::cout << tree2.get_item(2) << " (expected 22)" << std::endl;
  std::cout << tree2.get_item(3) << " (expected 11)" << std::endl;
  tree2.insert(4, 55);
  tree2.insert(5, 66);
  std::cout << tree.size() << " (expected 4)" << std::endl;
  std::cout << tree2.size() << " (expected 6)" << std::endl;
  std::cout << tree2.get_item(4) << " (expected 55)" << std::endl;
  std::cout << tree2.get_item(5) << " (expected 66)" << std::endl;
  // test advanced tree usage: range queries
  avl::avl_tree<double, std::greater<double>, std::size_t, avl::no_merge<double>,
    to_fstatistics_t, fstatistics_t, std::plus<fstatistics_t>, summarize_fstatistics_t>
    stat_tree;
  for(int i = 0; i < 100000; ++i) {
    stat_tree.insert(i / 3, sqrt(i) * sin(i));
  }
  std::cout << stat_tree.size() << " (expected 100000)" << std::endl;
  std::cout << stat_tree.get_item(999) << " (expected 51.446513094275254)" << std::endl;
  std::cout << stat_tree.get_item(123) << " (expected 5.545965544244308)" << std::endl;
  std::cout << stat_tree.get_item(4551) << " (expected 116.58825642773643)" << std::endl;
  std::cout << stat_tree.get_range(999, 1000) << " (expected 51.446513094275254, 51.446513094275254, 51.446513094275254)" << std::endl;
  std::cout << stat_tree.get_range(0, 100000) << " (expected -315.9551301692514, 0.002841886118341604, 315.8312974429844)" << std::endl;
  std::cout << stat_tree.get_range(98765, 99991) << " (expected -42.50917060359632, 0.010150295928113938, 42.767882804731585)" << std::endl;
  std::cout << stat_tree.get_range(123, 4567) << " (expected -116.54707776435288, 0.007742263529214008, 116.58825642773643)" << std::endl;
  std::cout << stat_tree.get_range(1, 11) << " (expected -4.058330490013714, 0.05384331878076476, 4.0828152807251294)" << std::endl;
  // test advanced tree usage: string operations
  avl::avl_tree<char, std::less<char>, std::size_t, avl::no_merge<char>, to_rhash_t> tstr;
  tstr.insert(0, 't');
  tstr.insert(1, 'e');
  tstr.insert(2, 's');
  tstr.insert(3, 't');
  tstr.insert(4, '?');
  std::cout << tstr.get_range(0, tstr.size()).value << " (expected 13569)" << std::endl;
  for(int i = 0; i < 13; ++i) {
    tstr.append(tstr);
  }
  std::cout << tstr.get_range(0, tstr.size()).value << " (expected 1641955328)" << std::endl;
  std::cout << tstr.get_range(0, 1000).value << " (expected 1153508880)" << std::endl;
  std::cout << tstr.get_range(4, 1004).value << " (expected 1963624016)" << std::endl;
  std::cout << tstr.get_range(3334, 4334).value << " (expected 1963624016)" << std::endl;
}
