#include <cmath>
#include <iostream>
#include "../avl_tree.cpp"
#include "xoroshiro128plus.h"

struct pp_t {
  double v;
  int n;
};

struct to_pp_t {
  pp_t operator () (double v) const {
    return pp_t{v, 1};
  }
};

pp_t operator+ (const pp_t& lhs, const pp_t& rhs) {
  return pp_t{lhs.v + rhs.v * pow(0.95, lhs.n), lhs.n + rhs.n};
}

struct from_pp_t {
  double operator() (const pp_t& v) const {
    return v.v;
  }
};

avl::avl_tree<double, std::greater<double>, std::size_t, avl::no_merge<double>, to_pp_t, pp_t, std::plus<pp_t>, from_pp_t> scores;

void print_top_scores() {
  auto n = scores.size();
  double pp = scores.get_range(0, n);
  std::cout << "# Nugget" << std::endl;
  std::cout << "Overall score: " << pp << std::endl;
  if(n < 11)return;
  std::cout << "Top 10 plays: (of " << n << ")" << std::endl;
  for(int i = 0; i < 10; ++i) {
    double raw_pp = scores.get_item(i);
    double weight = pow(0.95, i);
    std::cout << "* " << (raw_pp * weight) << "(" << raw_pp << " weighted " << (weight * 100) << "%)" << std::endl;
  }
}

int main() {
  // Simple test: insert 11
  for(int i = 0; i < 11; ++i) {
    scores.insert_ordered(i+1);
  }
  print_top_scores();
  // Generate 2M random scores
  xs gen(123, 456);
  for(int i = 0; i < 20; ++i) {
    for(int j = 0; j < 100000; ++j) {
      double v = (10 + i) * gen.next_double();
      v = v * v + 1;
      scores.insert_ordered(v);
    }
  }
  while(true) {
    print_top_scores();
    std::cout << "Enter a new score to insert." << std::endl;
    double v;
    std::cin >> v;
    if(!std::cin)break;
    int i = scores.insert_ordered(v);
    std::cout << "New " << (i+1) << "th best play worth " << v << " pp added" << std::endl;
  }
}
