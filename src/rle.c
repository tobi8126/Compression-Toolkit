#include <stdint.h>
#include <stdlib.h>
#include "rle.h"

#include <stdio.h>

int encode(const uint8_t input[], const size_t len, FILE* output) {
    if (input == NULL || output == NULL || len == 0) return -1;

    size_t i = 0;

    while (i < len) {
        //Wenn normaler run, keine Änderungen
        if (i+2 < len && input[i] == input[i+1] && input[i+1] == input[i+2]) {
            uint8_t count = 1;
            while (i+1 < len && input[i] == input[i+1] && count < 127) {
                count++;
                i++;
            }
            fwrite(&count, 1, 1, output);
            fputc(input[i], output);

            i++;
        }
        //Bei
        else {
            const size_t start_index = i;
            uint8_t count = 0b10000000;

            while (i < len && (count ^ 0b10000000) < 127) {
                if (i+2 < len && input[i] == input[i+1] && input[i+1] == input[i+2]) {
                    break;
                }

                count++;
                i++;
            }
            fwrite(&count, 1, 1, output);
            for (size_t j = 0; j < (count ^ 0b10000000); j++) {
                fputc(input[start_index + j], output);
            }
        }
    }
    return 0;
}

int decode(FILE *input, FILE* output) {
    if (input == NULL || output == NULL) return -1;

    int header;

    while ((header = fgetc(input)) != EOF) {
        uint8_t count = header;

        if (count & 0b10000000) {
            count ^= 0b10000000;

            for (int i = 0; i < count; i++) {
                const int c = fgetc(input);
                if (c != EOF) fputc(c, output);
            }
        }
        else {
            const int c = fgetc(input);
            for (size_t j = 0; j < count; j++) {
                if (c != EOF) fputc(c, output);
            }
        }
    }
    return 0;
}