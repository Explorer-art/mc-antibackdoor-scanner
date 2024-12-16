#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "scanner.h"
#include "utils.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s [plugin jar]\n", argv[0]);
		exit(1);
	}

    int whitelist_hash_count = 0;
    int blacklist_hash_count = 0;
    char** whitelist_hashes;
    char** blacklist_hashes;

    get_lines("whitelist_hashes.txt", &whitelist_hashes, &whitelist_hash_count);
    get_lines("blacklist_hashes.txt", &blacklist_hashes, &blacklist_hash_count);

    for (int i = 1; i < argc; i++) {
        printf("Plugin %s\n", argv[i]);

        float danger_level = plugin_scan(argv[i]);
        printf("Danger level: %.1f\n", danger_level);

        if (i != argc - 1) {
            printf("\n==============================\n\n");
        }
    }

	return 0;
}