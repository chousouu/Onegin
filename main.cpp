#include "Onegin.h"

int main()
{
    FILE *fp = OpenWriteFile("Hamlet.txt", "r");

    int SymbolsCnt = CountSymbols();  

    char *buffer = CopyToArr(fp, SymbolsCnt);
   // printf("allocated\n");

    OddSpaceRemoveArray(buffer);
    // printf("removed");

    int size = CountString(buffer);
    // printf("counted, %d\n", size);
    
    Strings *arr = FillInStruct(buffer, size);
    // printf("string\n");


    qsort(arr, size, sizeof(struct Strings), Compare);
 /*
    MSort(arr, 0, size - 1);
    printf("SORT");
*/
    PrintStrings(arr, size);
    // printf("PRINTD");
    free(arr);

}