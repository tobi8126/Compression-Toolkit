#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "rle.h"

#define CHUNK_SIZE 4096

int rle_file(const char *input_file_path, const char *output_file_path, const char mode) {
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

void print_usage(const char *prog_name) {
    printf("Usage: %s [decode: -d | encode: -e] -i <input.bin> [-o <output.rle>]\n", prog_name);
}

int main(int argc,char *argv[]) {
    int opt;
    char mode = '\0';
    const char *input_file_path = NULL;
    const char *output_file_path = NULL;

    while ((opt = getopt(argc, argv, "edi:o:")) != -1) {
        switch (opt) {
            case 'e':
                mode = 'e';
                break;

            case 'd':
                mode = 'd';
                break;

            case 'i':
                input_file_path = optarg;
                break;

            case 'o':
                output_file_path = optarg;
                break;

            case '?':
            default:
                print_usage(argv[0]);
                return -1;
        }
    }

    if (mode == '\0') {
        printf("Error: Must specify mode (encode|decode)\n");
        print_usage(argv[0]);
        return -1;
    }

    if (input_file_path == NULL) {
        printf("Error: Must specify input file using -i\n");
        print_usage(argv[0]);
        return -1;
    }

    rle_file(input_file_path, output_file_path, mode);
    return 0;
}
