#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <zip.h>
#include "utils.h"

unsigned char java_signature[] = { 0xCA, 0xFE, 0xBA, 0xBE };

void check_plugin(char* filename, unsigned char* code, zip_int64_t size, float* danger_level) {
	int signature_count;
    char** signatures;

    get_lines("signatures.txt", &signatures, &signature_count);

    unsigned char signature[4];

    if (memcmp(code, java_signature, sizeof(java_signature)) != 0) {
        printf("File %s is not java class\n", filename);
        return;
    }

    unsigned char* text = malloc(size);
    unsigned char* text_ptr = text;
    size_t i;

    for (i = 0; i < size; i++) {
    	if (is_ascii(code[i])) {
    		*text_ptr = code[i];
    		text_ptr++;
    	}
    }

    text_ptr[i] = '\0';

    bool safe = true;

    for (int i = 0; i < signature_count; i++) {
        if (strstr(text, signatures[i]) != NULL) {
            safe = false;
            (*danger_level)++;
            printf("Class %s: detected %s\n", filename, signatures[i]);
        }
    }

    free(text);
}

void plugin_scan(char* filename) {
	int err = 0;

	zip_t* archive = NULL;
	archive = zip_open(filename, 0, &err);

	struct zip_stat* finfo = NULL;
	finfo = calloc(256, sizeof(int));

	// Инициализация структуры информации о файле
	zip_stat_init(finfo);

	zip_file_t* fp = NULL;
	unsigned char* code = NULL;
	zip_int64_t file_count = zip_get_num_entries(archive, 0);
	float danger_level = 0;

	// Читаем файлы в архиве
	for (int i = 0; i < file_count; i++) {
		zip_stat_index(archive, i, 0, finfo);

		char* name = finfo->name;
		int name_length = strlen(name);

		if (name_length > 0 && name[name_length - 1] != '/') {
			if (strstr(name, ".class") != NULL) {
				code = calloc(finfo->size + 1, sizeof(unsigned char));
				fp = zip_fopen_index(archive, i, 0);
				zip_fread(fp, code, finfo->size);

				check_plugin(name, code, finfo->size, &danger_level);

				free(code);
			}
		}
	}

	printf("Danger level %.1f\n", danger_level);
}