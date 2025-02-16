//
// Created by intak on 14.02.2025.
//

#ifndef INC_1_FUNCTIONS_H
#define INC_1_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <io.h>
#include "structures.h"

void initFile(File *file, int n_arg, char *arg[]);
void openFile(File *file);
void setNumber(int* number);
void outFile(char* filename);
void enterFile(File *file);
void solve(File *file);
void delete(int pos, File *file);
void sort(File* file);
void deleteFile(File *file);

#endif //INC_1_FUNCTIONS_H
