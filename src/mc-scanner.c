#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

unsigned char java_signature[] = { 0xCA, 0xFE, 0xBA, 0xBE };

int main(int argc, char* argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s [plugin jar]\n", argv[0]);
		exit(1);
	}

    int signature_count;
    int whitelist_hash_count;
    int blacklist_hash_count;
    char** signatures;
    char** whitelist_hashes;
    char** blacklist_hashes;

    get_lines("signatures.txt", &signatures, &signature_count);
    get_lines("whitelist_hashes.txt", &whitelist_hashes, &whitelist_hash_count);
    get_lines("blacklist_hashes.txt", &blacklist_hashes, &blacklist_hash_count);

	FILE* fp = fopen(argv[1], "rb");

    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        exit(1);
    }

    unsigned char signature[4];

    fread(signature, 1, sizeof(signature), fp);

    if (memcmp(signature, java_signature, sizeof(java_signature)) != 0) {
        fprintf(stderr, "File %s is not java class\n", argv[1]);
        exit(1);
    }

    char hash[65];

    if (!calc_sha256(argv[1], hash)) {
        fprintf(stderr, "Error hash calculation\n");
        exit(1);
    }

    printf("SHA256: %s\n\n", hash);

    fseek(fp, 0, SEEK_SET);

    int bytes_read;
    unsigned char buffer[BUFFER_SIZE];
    long size = get_filesize(argv[1]);
    unsigned char* text = malloc(size + 1);
    unsigned char* text_ptr = text;

	while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            if (is_ascii(buffer[i])) {
                *text_ptr = buffer[i];
                text_ptr++;
            }
        }
    }

    fclose(fp);

    *text_ptr = '\0';

    bool safe = true;
    float danger_level = 0;

    for (int i = 0; i < signature_count; i++) {
        if (strstr(text, signatures[i]) != NULL) {
            safe = false;
            danger_level++;
            printf("Detected %s\n", signatures[i]);
        }
    }

    free(text);

    printf("Danger level: %.1f\n", danger_level);

	return 0;
}