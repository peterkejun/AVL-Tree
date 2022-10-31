#include <iostream>
#include "xoroshiro128plus.h"
#include "text_main.h"

uint64_t stats_totalq = 0;
uint64_t stats_insert = 0;
uint64_t stats_delete = 0;
uint64_t stats_adelete = 0;
uint64_t stats_adelete_b = 0;
uint64_t stats_copypaste = 0;
uint64_t stats_copypaste_b = 0;
uint64_t stats_cutpaste = 0;
uint64_t stats_cutpaste_b = 0;
uint64_t stats_eq = 0;
uint64_t checksum = 1;
xs gen(533, 8293);

void query_copypaste() {
  uint64_t n = internal_get_size();
  uint64_t sl = gen.next() % (n + 1);
  uint64_t i = gen.next() % (n + 1 - sl);
  uint64_t j = gen.next() % (n + 1);
  internal_copypaste(i, i+sl, j);
  stats_totalq++;
  stats_copypaste++;
  stats_copypaste_b+=sl;
}

void query_cutpaste() {
  uint64_t n = internal_get_size();
  uint64_t sl = gen.next() % (n + 1);
  uint64_t i = gen.next() % (n + 1 - sl);
  uint64_t j = gen.next() % (n + 1 - sl);
  internal_cutpaste(i, i+sl, j);
  stats_totalq++;
  stats_cutpaste++;
  stats_cutpaste_b+=sl;
}

void query_adelete() {
  uint64_t n = internal_get_size();
  uint64_t sl = gen.next() % (n/4 + 1);
  uint64_t i = gen.next() % (n + 1 - sl);
  internal_delete(i, i+sl);
  stats_totalq++;
  stats_adelete++;
  stats_adelete_b+=sl;
}

void query_equal() {
  uint64_t n = internal_get_size();
  uint64_t sl = 2 + gen.next() % 2;
  if(sl > 2) {
    sl = 2 + gen.next() % (n - 4);
  }
  uint64_t i = gen.next() % (n + 1 - sl);
  uint64_t j = gen.next() % (n + 1 - sl);
  if(internal_test_equal(i, i+sl, j)) {
    checksum += 1;
  }
  stats_totalq++;
  stats_eq++;
  checksum *= 201097;
  checksum ^= checksum >> 13;
}

void query_insert() {
  uint64_t n = internal_get_size();
  uint64_t index = gen.next() % (n + 1);
  char c = 'a' + (gen.next() % 100000) / 99999;
  internal_insert(index, c);
  stats_totalq++;
  stats_insert++;
}

void query_delete() {
  uint64_t n = internal_get_size();
  uint64_t index = gen.next() % n;
  internal_delete(index);
  stats_totalq++;
  stats_delete++;
}

void print_round_summary() {
  std::cout << "-------------------- " << internal_versionid() << " --------------------" << std::endl;
  std::cout << "Text document currently " << (internal_get_size() >> 20) << " MiB after " << stats_totalq << " total operations" << std::endl;
  std::cout << "Checksum value " << checksum << " (" << stats_eq << " tests)" << std::endl;
  std::cout << stats_insert << " chars typed, " << stats_delete << " lone chars deleted" << std::endl;
  std::cout << (stats_adelete_b >> 20) << " MiB deleted over " << stats_adelete << " select/delete operations" << std::endl;
  std::cout << (stats_copypaste_b >> 20) << " MiB pasted over " << stats_copypaste << " copy/paste operations" << std::endl;
  std::cout << (stats_cutpaste_b >> 20) << " MiB pasted over " << stats_cutpaste << " cut/paste operations" << std::endl;
}

int main() {
  while(1) {
    for(int ii = 0; ii < 200; ++ii) {
      uint64_t op = gen.next() & 255;
      uint64_t n = internal_get_size();
      if(op < 3 && n > 1000 && n < 400000000) {
        query_copypaste();
      }else if(op < 4 && n > 1000) {
        query_cutpaste();
      }else if(op < 5 && n > 1000) {
        query_adelete();
      }else if(op < 30 && n > 1000) {
        query_equal();
      }else if(n < 1000 || op < 170 && n < 400000000) {
        query_insert();
      }else {
        query_delete();
      }
    }
    print_round_summary();
  }
}
