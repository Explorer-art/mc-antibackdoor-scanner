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

    char hash[65];

    if (!calc_sha256(argv[1], hash)) {
        fprintf(stderr, "Error hash calculation\n");
        exit(1);
    }

    printf("SHA256: %s\n\n", hash);

    plugin_scan(argv[1]);

	return 0;
}