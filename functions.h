//
// Created by intak on 14.02.2025.
//

#ifndef INC_1_FUNCTIONS_H
#define INC_1_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <string.h>
#include <io.h>
#include "structures.h"

void initFile(File *file);
void setNumber(int* number);
void outFile(char* filename);
void enterFile(File *file);
void solve(int* ans, int x, File *file);
void delete(int pos, File *file);
void mergeSort(int** array, int n);
void sort(File* file);
#endif //INC_1_FUNCTIONS_H
