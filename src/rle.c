//
// Created by tobia on 22.09.2026.
//

#include <stddef.h>
#include <string.h>
#include "rle.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

char* encode(char* input) {
    if (input == NULL) return NULL;

    const size_t len = strlen(input);
    char* encoded = malloc(strlen(input) * 2 + 1 * sizeof(char));
    char* start = encoded;

    for (int i = 0; i < len; i++) {
        int counter = 1;
        char c = input[i];
        while (c == input[i+1]) {
            counter++;
            i++;
        }

        *encoded++ = c;
        *encoded++ = counter;
    }
    *encoded = '\0';
    return start;
}

char* decode(char* input) {
    if (input == NULL) return NULL;
    const size_t len = strlen(input);
    size_t capacity = len * 2;
    char* decoded = malloc(capacity * sizeof(char));
    char* current = decoded;

    for (int i = 0; input[i] != '\0'; i += 2) {
        for (int j = 0; j < input[i+1]; j++) {
            if (current - decoded >= capacity) {
                capacity *= 2;
                char* temp = realloc(decoded, capacity * sizeof(char));
                if (temp == NULL) {return NULL;}

                decoded = temp;
                current = decoded + (current - decoded);
            }
            *current++ = input[i];
        }
    }

    *current = '\0';
    return decoded;
}