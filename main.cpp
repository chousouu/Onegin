#include "Onegin.h"

int main()
{
    FILE *fp = fopen("Hamlet.txt", "r");
    int SymbolsCnt = CountSymbols();  

    printf("%d\n", SymbolsCnt);

    char *buffer = SpaceRemoveAndCopyToArr(SymbolsCnt, fp);

    printf("allocated\n");

    //printf("%s", buffer);

    int size = CountString(buffer);
    printf("counted, %d\n", size);
    
    Strings *arr = FillInStruct(buffer, size);
    printf("string\n");


    //qsort(arr, size, sizeof(struct Strings), Compare);
 
    MSort(arr, 0, size - 1);
    printf("SORT");

    PrintStrings(arr, size);
    printf("PRINTD");
    free(arr);

}

