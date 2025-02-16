//
// Created by intak on 14.02.2025.
//

#include "functions.h"
void initFile(File *file)
{
    file->name = (char*)malloc(sizeof(char)*20);
    printf("Enter filename\n");
    if (!fgets(file->name, 20, stdin)){
        printf("\nWrong filename");
        system("pause");
        exit(1);
    }
    file->name[strlen(file->name)-1] = '\0';
    file->size = 0;
    enterFile(file);
    outFile(file->name);
}
void openFile(File *file)
{
    file->myFile = fopen(file->name, "r+b");
    if(!file->myFile)
    {
        printf("Cant open file\n");
        system("pause");
        exit(0);
    }
}
void solve(File *file)
{

printf("\nEnter a number\n");
int x;
setNumber(&x);

int ans = 0;
openFile(file);
int num, pos = 0;
while(fread(&num, sizeof(int), 1, file->myFile))
{
    if(num < x){
    ans++;
    delete(pos--, file, 0);
    }
    pos++;
}
fclose(file->myFile);

printf("Number of elements less than X are %d\n", ans);
printf("Here is changed array\n");
outFile(file->name);

sort(file);
printf("Here is your sorted file\n");
outFile(file->name);
}

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
    file->myFile = fopen(file->name, "wb");
    if(!file->myFile)
    {
        printf("Cant open file\n");
        system("pause");
        exit(0);
    }
    printf("enter array elements\n");
    int num;
    for(int i = 0;i<file->size;++i) {
        setNumber(&num);
        fwrite(&num, sizeof(int), 1, file->myFile);
    }
    fclose(file->myFile);
    printf("File has been written\n");
}
void outFile(char* filename)
{
    FILE *f = fopen(filename, "r+b");
    if(!f)
    {
        printf("Cant open file\n");
        system("pause");
        exit(0);
    }
    int num;
    while(fread(&num, sizeof(int), 1, f))
    {
        printf("%d ", num);
    }
    printf("\n");
    fclose(f);
}
void swapInFile(int i, int j, File *file)
{
        int num1, num2;
        int pos1 = i * (int)sizeof(int), pos2 = j * (int)sizeof(int);

        fseek(file->myFile, pos1, SEEK_SET);
        fread(&num1, sizeof(int), 1, file->myFile);

        fseek(file->myFile, pos2, SEEK_SET);
        fread(&num2, sizeof(int), 1, file->myFile);

        fseek(file->myFile, pos1, SEEK_SET);
        fwrite(&num2, sizeof(int), 1, file->myFile);

        fseek(file->myFile, pos2, SEEK_SET);
        fwrite(&num1, sizeof(int), 1, file->myFile);
}
void delete(int pos, File *file, int flag)
{
    int num;
    for (int i = pos+1; i < file->size; i++) {

        int readPos = i * (int)sizeof(int);
        int writePos = (i-1) * (int)sizeof(int);

        fseek(file->myFile, readPos, SEEK_SET);
        fread(&num, sizeof(int), 1, file->myFile);

        fseek(file->myFile, writePos, SEEK_SET);
        fwrite(&num, sizeof(int), 1, file->myFile);
    }
    if(!flag){file->size--;}
    int POS = pos * (int)sizeof(int);
    _chsize(fileno(file->myFile), ftell(file->myFile));
    fseek(file->myFile, POS, SEEK_SET);
}
void sort(File* file)
{
    openFile(file);
    int num1;
    for(int i = 0;i < file->size-1; ++i)
    {
        int pos1 = i * (int)sizeof(int);
        fseek(file->myFile, pos1, SEEK_SET);
        fread(&num1, sizeof(int), 1, file->myFile);
        int num2;
        for(int j = i; j<file->size; ++j)
        {
            int pos2 = j * (int)sizeof(int);
            fseek(file->myFile, pos2, SEEK_SET);
            fread(&num2, sizeof(int), 1, file->myFile);
            if(num1 < num2){ swapInFile(i, j, file);}
        }
    }
    fclose(file->myFile);
}
