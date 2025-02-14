//
// Created by intak on 14.02.2025.
//

#include "functions.h"
void setNumber(int* number)
{
    int isInvalid = 0;
    do {
        isInvalid = 0;
        int i = 0;
        *number = 0;
        char digits[50];
        scanf("%s", digits);
        int negative = 1;
        if(digits[0] == '-'){negative = -1;i++;}
        do {
            if (digits[i] < '0' || digits[i] > '9') {
                printf("Enter a valid number\n");
                isInvalid = 1;
                while(getchar()!='\n');
                break;
            }
            else {*number = *number * 10 + digits[i] - '0'; }
        } while(digits[++i] != 0);
        *number *= negative;
    }while(isInvalid == 1);
    while(getchar()!='\n');
}
void enterFile(File *file)
{
    printf("enter size of the array\n");
    setNumber(&file->size);
    file->arr = (int*)malloc(file->size * sizeof(int));
    file->myFile = fopen(file->name, "wb");
    if(!file->myFile)
    {
        printf("Cant open file\n");
        system("pause");
        exit(0);
    }
    printf("enter array elements\n");
    for(int i = 0;i<file->size;++i)
    {
        setNumber(&file->arr[i]);
    }
    fwrite(file->arr, sizeof(int), file->size, file->myFile);
    fclose(file->myFile);
    printf("File has been written\n");
}
void outFile(char* filename)
{
    int* buffer = (int*)malloc(sizeof(int) * 256);
    FILE *f = fopen(filename, "r+b");
    if(!f)
    {
        printf("Cant open file\n");
        system("pause");
        exit(0);
    }
    unsigned int size = fread(buffer, sizeof(int), 256, f);
    for(int i = 0;i<size;++i)
    {
        printf("%d ", buffer[i]);
    }
    free(buffer);
    fclose(f);
}
void solve(int* ans, int x, File *file)
{
    file->myFile = fopen(file->name, "r+b");
    if(!file->myFile)
    {
        printf("Cant open file\n");
        system("pause");
        exit(0);
    }
    for(int i = 0;i<file->size;++i)
    {
        if(file->arr[i] < x){
            (*ans)++;
            delete(i--, file);
        }
    }
    fclose(file->myFile);
}
void delete(int pos, File *file)
{
    for (int i = pos; i + 1 < file->size; ++i)
        file->arr[i] = file->arr[i + 1];

    file->size--;
    rewind(file->myFile);
    fwrite(file->arr, sizeof(int), file->size, file->myFile);
    _chsize(fileno(file->myFile), file->size);
    fseek(file->myFile, pos, SEEK_SET);
}
void sort(File* file)
{

    file->myFile = fopen(file->name, "r+b");
    if(!file->myFile)
    {
        printf("Cant open file\n");
        system("pause");
        exit(0);
    }
    mergeSort(&file->arr, file->size);
    rewind(file->myFile);
    fwrite(file->arr, sizeof(int), file->size, file->myFile);
    _chsize(fileno(file->myFile), ftell(file->myFile));
    fclose(file->myFile);
}
void mergeSort(int** array, int n)
{
    int right, rend;
    int i, j, m;
    int* newArray = calloc(n, sizeof(int) );
    if(newArray == NULL){printf("memory cant be allocated\n");return;}
    for (int k = 1; k < n; k<<=1)
    {
        for (int left = 0; left + k < n; left += k<<1)
        {
            right = left + k;
            rend = right + k;
            if (rend > n) rend = n;
            m = left; i = left; j = right;
            while (i < right && j < rend)
            {
                if ((*array)[i] >= (*array)[j]) {newArray[m] = (*array)[i++]; }
                else {newArray[m] = (*array)[j++];}
                m++;
            }
            while (i < right)
                newArray[m++] = (*array)[i++];

            while (j < rend)
                newArray[m++] = (*array)[j++];

            for (i = left; i < rend; i++)
                (*array)[i] = newArray[i];
        }
    }
    free(newArray);
}