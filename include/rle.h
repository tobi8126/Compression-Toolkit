//
// Created by tobia on 22.09.2026.
//
#pragma once
#include <stdio.h>

#ifndef COMPRESSIONTOOLKIT_CLE_H
#define COMPRESSIONTOOLKIT_CLE_H


int encode(const uint8_t input[], size_t len, FILE *output);

int decode(FILE *input, FILE *output);

#endif //COMPRESSIONTOOLKIT_CLE_H