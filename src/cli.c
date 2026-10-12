//
// Created by tobia on 12.10.2026.
//

#include "cli.h"

#include <getopt.h>
#include <stdio.h>

#include "file.h"

void print_usage(const char *prog_name) {
    printf("Usage: %s [compress: -c | decompress: -d] -i <input.bin> [-o <output.rle>]\n", prog_name);
}

int cli_and_run(const int argc, char *argv[]) {
    int opt;
    char mode = '\0';
    const char *input_file_path = NULL;
    const char *output_file_path = NULL;

    while ((opt = getopt(argc, argv, "cdi:o:")) != -1) {
        switch (opt) {
            case 'c':
                mode = 'c';
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
        printf("Error: Must specify mode (compress|decompress)\n");
        print_usage(argv[0]);
        return -1;
    }

    if (input_file_path == NULL) {
        printf("Error: Must specify input file using -i\n");
        print_usage(argv[0]);
        return -1;
    }

    return rle_file(input_file_path, output_file_path, mode);
}