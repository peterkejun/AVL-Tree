#ifndef __TEXT_DEMO_MAIN_H__
#define __TEXT_DEMO_MAIN_H__
char* internal_versionid();
int internal_get_size();
void internal_insert(int index, char c);
void internal_delete(int index);
void internal_delete(int start, int stop);
void internal_copypaste(int start, int stop, int dst);
void internal_cutpaste(int start, int stop, int dst);
bool internal_test_equal(int start, int stop, int start_2);
#endif
