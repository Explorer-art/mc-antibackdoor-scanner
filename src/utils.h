#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define BUFFER_SIZE 1024

int is_ascii(unsigned char c);
int get_filesize(char* filename);
bool calc_sha256(char* filename, char* output);
void get_lines(char* filename, char*** lines, int* line_count_output);

#endif