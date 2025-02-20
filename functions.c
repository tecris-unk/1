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
rewind(stdin);
}
void scanString(char **string, int *size)
{
    *string = NULL;
    resize(string, 0);
    int c;
    for(int i=0;(c=getchar())!='\n' && c != EOF ;++i)
    {
        *size = i+1;
        resize(string, *size);
        (*string)[i] = (char) c;
    }
}
void resize(char** array, int size)
{
    char *temp = NULL;
    temp = (char*)realloc(*array, sizeof(char) * (size+1));
    if(temp == NULL){
        printf("memory cant be allocated\n");
        free(temp);
        exit(1);
    }
    else{
        *array = (char*)temp;
        (*array)[size] = '\0';
    }
}
void strCat(char** string, int size, const char* sumString)
{
    int i = 0;
     while(sumString[i]!='\0' && sumString[i] != EOF)
     {
         resize(string, size+i+1);
         (*string)[size+i] = sumString[i];
         i++;
     }
}
void coutString(char* string)
{
    for(int i = 0; string[i] != '\0'; ++i)
        printf("%c", string[i]);
}
void initFile(File *file, int n_arg, char *arg[])
{
    char* bin =".bin\0";

    int size = 0;
    if (n_arg > 1){
        file->name = (char*)malloc(sizeof(arg[1]));
        if(file->name == NULL){fprintf(stderr, "memory cant be allocated\n");exit(1);}
        file->name = arg[1];
    }
    else {
        printf("Enter file name: ");
        scanString(&file->name, &size);
    }
    printf("%d\n", size);
    strCat(&file->name, size, bin);
    free(bin);
    coutString(file->name);
    printf("\n");
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
    printf("%d\n", num);
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
    if(pos + 1 == file->size){
        file->size--;
        _chsize(_fileno(file->myFile), (long)file->size * (long)sizeof(int));
        fseek(file->myFile, pos * (int)sizeof(int), SEEK_SET);
        return;
    }
    int num;
    for (int i = pos+1; i < file->size; i++)
    {
        readNum(i, &num, file);
        writeNum(i-1, &num, file);
    }
    file->size--;
    _chsize(fileno(file->myFile), ftell(file->myFile));
    fseek(file->myFile, pos * (int)sizeof(int), SEEK_SET);
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
            if(num1 < num2){swapInFile(i, j, file);num1 = num2;}
        }
    }
    fclose(file->myFile);
}
void deleteFile(File *file)
{
    remove(file->name);
    free(file->name);
}
