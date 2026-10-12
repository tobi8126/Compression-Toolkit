#include <stdint.h>
#include <stdlib.h>
#include "rle.h"

#include <stdio.h>

int encode(const uint8_t input[], const size_t len, FILE* output) {
    if (input == NULL || output == NULL || len == 0) return -1;

    size_t i = 0;

    while (i < len) {
        //Bei Byte-Wiederholung: keine Änderung
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
        //Keine Byte-Wiederholung: MSB auf 1 als Flag für decode und die Länge des Run's zählen
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
                const int current_run_byte = fgetc(input);
                if (current_run_byte != EOF) fputc(current_run_byte, output);
            }
        }
        else {
            const int repeat_byte = fgetc(input);
            for (size_t i = 0; i < count; i++) {
                if (repeat_byte != EOF) fputc(repeat_byte, output);
            }
        }
    }
    return 0;
}