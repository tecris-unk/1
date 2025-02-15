
#include "functions.h"

int main()
{
    File file;
    initFile(&file);

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