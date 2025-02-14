
#include "functions.h"

int main()
{
    File file;
    file.name = (char*)malloc(sizeof(char)*20);
    printf("Enter filename\n");
    if (!fgets(file.name, 20, stdin)){
        printf("\nWrong filename");
        return 1;
    }
    file.name[strlen(file.name)-1] = '\0';
    file.size = 0;

    enterFile(&file);
    outFile(file.name);

    printf("\nEnter a number\n");
    int x;
    setNumber(&x);

    int ans = 0;
    solve(&ans, x,  &file);
    printf("Number of elements less than X are %d\n", ans);
    printf("Here is changed array\n");
    outFile(file.name);
    printf("\n");
    sort(&file);
    printf("Here is your sorted file\n");
    outFile(file.name);
    printf("\n");
    system("pause");
    return 0;
}