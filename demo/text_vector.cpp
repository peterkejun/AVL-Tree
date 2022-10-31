#include <cstring>
#include <vector>
#include "text_main.h"

std::vector<char> vec;

char* internal_versionid() {
  return "std::vector version";
}

int internal_get_size() {
  return vec.size();
}

void internal_insert(int index, char c) {
  vec.insert(vec.begin() + index, c);
}

void internal_delete(int index) {
  vec.erase(vec.begin() + index);
}

void internal_delete(int start, int stop) {
  vec.erase(vec.begin() + start, vec.begin() + stop);
}

void internal_copypaste(int start, int stop, int dst) {
  char* buf = new char[stop - start];
  memcpy(buf, &(vec[start]), stop - start);
  vec.insert(vec.begin() + dst, buf, buf + stop - start);
  delete buf;
}

void internal_cutpaste(int start, int stop, int dst) {
  char* buf = new char[stop - start];
  memcpy(buf, &(vec[start]), stop - start);
  vec.erase(vec.begin() + start, vec.begin() + stop);
  vec.insert(vec.begin() + dst, buf, buf + stop - start);
  delete buf;
}

bool internal_test_equal(int start, int stop, int start_2) {
  return 0 == strncmp(&(vec[start]), &(vec[start_2]), stop - start);
}

#include "text_main.cpp"
