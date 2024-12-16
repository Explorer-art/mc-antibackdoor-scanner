#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define BUFFER_SIZE 1024

extern char** backdoor_signatures;
extern int signature_count;

int is_ascii(unsigned char c);
int get_filesize(char* filename);
bool calc_sha256(char* filename, char* output);
bool load_signatures(char* filename);

#endif