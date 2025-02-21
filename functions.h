//
// Created by intak on 14.02.2025.
//

#ifndef INC_1_FUNCTIONS_H
#define INC_1_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <io.h>
#include "structures.h"
void scanString(char **string, int *size);
void resize(char** array, int size);
void strCat(char** string, int size, const char* sumString);
void coutString(char* string);
void initFile(File *file, int n_arg, char *arg[]);
void strSize(char *string, int* size);
void openFile(File *file);
void setNumber(int* number);
void outFile(char* filename);
void enterFile(File *file);
void readNum(int pos, int *num, File *file);
void writeNum(int pos, int *num, File *file);
void solve(File *file);
void delete(int pos, File *file);
void sort(File* file);
void deleteFile(File *file);

#endif //INC_1_FUNCTIONS_H
