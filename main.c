
#include "functions.h"

int main(int n_arg, char *arg[])
{
    File file;
    initFile(&file, n_arg, arg);

    solve(&file);

    deleteFile(&file);
}