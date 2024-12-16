#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "utils.h"

int is_ascii(unsigned char c) {
    return (c >= 32 && c <= 127);
}

int get_filesize(char* filename) {
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    long size;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fclose(fp);

    return size;
}

void sha256_hash_string(unsigned char hash[SHA256_DIGEST_LENGTH], char output[65]) {
    int i = 0;

    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }

    output[64] = 0;
}

bool calc_sha256(char* filename, char output[65]) {
    FILE* fp = fopen(filename, "rb");

    if (fp == NULL) {
        return false;
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    const int buffer_size = 32768;
    char* buffer = malloc(buffer_size);
    int bytes_read = 0;

    if (!buffer) {
        return false;
    }

    while (bytes_read = fread(buffer, 1, buffer_size, fp)) {
        SHA256_Update(&sha256, buffer, bytes_read);
    }

    SHA256_Final(hash, &sha256);

    sha256_hash_string(hash, output);
    fclose(fp);
    free(buffer);

    return true;
}

void get_lines(char* filename, char*** lines, int* line_count_output) {
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        fprintf(stderr, "Error opening %s file\n", filename);
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    int line_count = 0;

    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        line_count++;
    }

    fseek(fp, 0, SEEK_SET);

    *lines = malloc(line_count * sizeof(char*));
    char* signature;
    int i = 0;

    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        signature = malloc(strlen(buffer) + 1);
        strcpy(signature, buffer);
        signature[strcspn(buffer, "\n")] = '\0';
        (*lines)[i] = signature;
        i++;
    }

    fclose(fp);
    
    *line_count_output = line_count;
}