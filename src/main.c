#include <stdio.h>
#include "rle.h"

int main(void) {
    char* original = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    char* encoded = encode(original);
    char* decoded = decode(encoded);
    printf("Original Text: %s\n",original);
    printf("Encoded  Text: %s\n", encoded);
    printf("Decoded  Text: %s\n", decoded);
    return 0;
}
