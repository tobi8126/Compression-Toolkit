//
// Created by tobia on 12.10.2026.
//

#include "file.h"

#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "rle.h"

#define CHUNK_SIZE 4096

const uint8_t MAGIC_NUMBER[3] = {'R', 'L', 'E'};

int rle_file(const char *input_file_path, const char *output_file_path, const char mode) {
    if (mode != 'c' && mode != 'd') {
        return -1;
    }

    FILE *input = fopen(input_file_path, "rb");
    if (input == NULL) {
        perror("Failed to open input file");
        return -1;
    }

    FILE *output = fopen((output_file_path == NULL) ? "../out/rle_output_file.rle" : output_file_path, "wb");
    if (output == NULL) {
        perror("Failed to open output file");
        return -1;
    }

    if (mode == 'c') {
        const clock_t start = clock();

        fwrite(MAGIC_NUMBER, 1, 3, output);

        uint8_t buffer[CHUNK_SIZE];
        size_t bytes_read;

        while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, input)) > 0) {
            if (encode(buffer, bytes_read, output) != 0) return -1;
        }
        const clock_t end = clock();
        const double elapsed_time = difftime(end, start);

        fseek(input, 0L, SEEK_END);
        const long input_file_size = ftell(input);

        fseek(output, 0L, SEEK_END);
        fflush(output);
        const long output_file_size = ftell(output);

        float ratio = 0;
        if (input_file_size > 0)
            ratio = (float)output_file_size / (float)input_file_size;

        setlocale(LC_NUMERIC, "");
        printf("Input:  %'15ld bytes\n"
                     "Output: %'15ld bytes\n"
                     "\n"
                     "Compression ratio: %.2f%%\n"
                     "Space saved:       %.2f%%\n"
                     "\n"
                     "Encoding time:     %.1f ms",
                     input_file_size, output_file_size, ratio * 100, (1-ratio) * 100, elapsed_time);
    }
    if (mode == 'd') {
        uint8_t header[3];
        if (fread(header, 1, 3, input) != 3) {
            printf("Fehler: Datei ist zu klein oder leer.\n");
            fclose(input);
            fclose(output);
            return -1;
        }

        if (memcmp(header, MAGIC_NUMBER, 3) != 0) {
            printf("Fehler: Keine Gültige .rle Datei.\n");
            fclose(input);
            fclose(output);
            remove((output_file_path == NULL) ? "../out/rle_output_file.rle" : output_file_path);
            return -1;
        }

        if (decode(input, output) != 0) return -1;
    }

    fclose(input);
    fclose(output);
    return 0;
}
