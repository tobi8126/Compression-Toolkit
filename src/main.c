#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rle.h"

#define CHUNK_SIZE 4096

int rle_file(const char *input_file_path, const char *output_file_path, char mode) {
    if (mode != 'e' && mode != 'd') {
        return -1;
    }

    FILE *input = fopen(input_file_path, "rb");
    if (input == NULL) {
        perror("Failed to open input file");
        return -1;
    }

    FILE *output = fopen((output_file_path == NULL) ? "..\\out\\rle_compressed_file.rle" : output_file_path, "wb");
    if (output == NULL) {
        perror("Failed to open output file");
        return -1;
    }

    if (mode == 'e') {
        uint8_t buffer[CHUNK_SIZE];
        size_t bytes_read;

        while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, input)) > 0) {
            encode(buffer, bytes_read, output);
        }
    }
    if (mode == 'd') {
        decode(input, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}

int main(int argc,char *argv[]) {

    if (argc < 3 || argc > 4 || strlen(argv[1]) > 1 || rle_file(argv[2], (argc == 4) ? argv[3] : NULL, argv[1][0]) < 0) {
        printf("Usage Instructions: use input file path and optional output file path as argument. \n"
               "compressionToolkit.exe <mode (decode: d, encode: e> <inputfilepath> <outputfilepath>\n");
        return -1;
    }

    return 0;
}
