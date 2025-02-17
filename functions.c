//
// Created by intak on 14.02.2025.
//

#include "functions.h"
void initFile(File *file, int n_arg, char *arg[])
{
    if (n_arg > 1){
        file->name = (char*)malloc(sizeof(arg[1]));
        file->name = arg[1];
    }
    else {
        file->name = (char*)malloc(sizeof(char)*24);
        //ограничение на название файла 20 символов.
        printf("Enter file name: ");
        if (!fgets(file->name, 20, stdin)){
            printf("\nWrong file name");
            exit(1);
        }
        file->name[strlen(file->name)-1] = '\0';
        char bin[5] = ".bin" ; bin[4] ='\0';
        file->name = strcat(file->name,bin);
    }
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
    delete(pos--, file);
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
        char digits[10];
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
    FILE *f = fopen(filename, "rb");
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
void readNum(int pos, int *num, File *file)
{
    fseek(file->myFile, pos * (int)sizeof(int), SEEK_SET);
    fread(num, sizeof(int), 1, file->myFile);
}
void writeNum(int pos, int *num, File *file)
{
    fseek(file->myFile, pos * (int)sizeof(int), SEEK_SET);
    fwrite(num, sizeof(int), 1, file->myFile);
}
void swapInFile(int i, int j, File *file)
{
        int num1, num2;
        readNum(i, &num1, file);
        readNum(j, &num2, file);
        writeNum(i, &num2, file);
        writeNum(j, &num1, file);
}
void delete(int pos, File *file)
{
    int num;
    for (int i = pos+1; i < file->size; i++)
    {
        readNum(i, &num, file);
        writeNum(i-1, &num, file);
    }
    file->size--;
    _chsize(fileno(file->myFile), ftell(file->myFile));
    int POS = pos * (int)sizeof(int);
    fseek(file->myFile, POS, SEEK_SET);
}
void sort(File* file)
{
    openFile(file);
    int num1;
    for(int i = 0;i < file->size-1; ++i)
    {
        readNum(i, &num1, file);
        int num2;
        for(int j = i+1; j<file->size; ++j)
        {
            readNum(j, &num2, file);
            if(num1 < num2){swapInFile(i, j, file);}
        }
    }
    fclose(file->myFile);
}
void deleteFile(File *file)
{
    remove(file->name);
    free(file->name);
}