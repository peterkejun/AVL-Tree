#include "../avl_tree.cpp"
#include "text_main.h"

// WARNING! ACTUALLY SEGFAULTS!

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
    return rhash_t{(unsigned int)v, 1};
  }
};

typedef avl::avl_node<char, int, rhash_t> dnode_t;

dnode_t* root = nullptr;
std::less<char> _less;
avl::no_merge<char> _merge;
to_rhash_t _rpre;
std::plus<rhash_t> _rcomb;
std::allocator<dnode_t> _alloc;

char* internal_versionid() {
  return "avl version";
}

int internal_get_size() {
  return avl::avl_node_size(root);
}

void internal_insert(int index, char c) {
  root = std::get<0>(avl::avl_node_insert_at_index(
      root, index,
      c, _merge, _rpre,
      _rcomb, _alloc));
}

void internal_delete(int index) {
  root = std::get<0>(avl::avl_node_remove_at_index(
      root, index,
      _rpre, _rcomb,
      _alloc));
}

void internal_delete(int start, int stop) {
  dnode_t *l, *m, *r;
  std::tie(m, r) = avl::avl_node_split(
    root, stop, _merge, _rpre, _rcomb, _alloc);
  std::tie(l, m) = avl::avl_node_split(
    m, start, _merge, _rpre, _rcomb, _alloc);
  root = avl::avl_node_join2(l, r, _rpre, _rcomb, _alloc);
  avl::avl_node_delete_subtree(m, _alloc);
}

void internal_copypaste(int start, int stop, int dst) {
  dnode_t* splicer = nullptr;
  for(int i = start; i < stop; ++i) {
    splicer = std::get<0>(avl::avl_node_insert_at_index(
        splicer, i - start,
        avl_node_get_at_index(root, i), _merge, _rpre,
        _rcomb, _alloc));
  }
  dnode_t *l, *r;
  std::tie(l, r) = avl::avl_node_split(
    root, dst, _merge, _rpre, _rcomb, _alloc);
  root = avl::avl_node_join2(l, splicer, _rpre, _rcomb, _alloc);
  root = avl::avl_node_join2(root, r, _rpre, _rcomb, _alloc);
}

void internal_cutpaste(int start, int stop, int dst) {
  dnode_t *l, *m, *r;
  std::tie(m, r) = avl::avl_node_split(
    root, stop, _merge, _rpre, _rcomb, _alloc);
  std::tie(l, m) = avl::avl_node_split(
    m, start, _merge, _rpre, _rcomb, _alloc);
  root = avl::avl_node_join2(l, r, _rpre, _rcomb, _alloc);
  std::tie(l, r) = avl::avl_node_split(
    root, dst, _merge, _rpre, _rcomb, _alloc);
  root = avl::avl_node_join2(l, m, _rpre, _rcomb, _alloc);
  root = avl::avl_node_join2(root, r, _rpre, _rcomb, _alloc);
}

bool internal_test_equal(int start, int stop, int start_2) {
  return avl_node_range_get(root, start, stop, _rpre, _rcomb).value
    == avl_node_range_get(root, start_2, start_2 + stop - start, _rpre, _rcomb).value;
}

#include "text_main.cpp"
