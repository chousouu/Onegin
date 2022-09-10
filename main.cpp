#include "Onegin.h"

int main()
{
    FILE *fp = fopen("Hamlet.txt", "r");
    char *buffer = (char*)calloc(CountSymbols(fp), sizeof(char));
    printf("allocated\n");

    SpaceRemoveAndCopyToArr(buffer, fp);
    printf("remied\n");

    int size = CountString(buffer);
    printf("counted, %d\n", size);
  
    struct Strings * arr = (struct Strings *)calloc(size, sizeof(struct Strings)); 

    GetString(buffer, arr, size);
    printf("string\n");

    
    MSort(arr, 0, size);
    printf("SORT");

    PrintStrings(arr, size - 1);
    printf("PRINTD");

    free(arr);

}

