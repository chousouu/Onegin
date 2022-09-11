#include "Onegin.h"

int main()
{
    FILE *fp = OpenFile();
    assert(fp);

    int SymbolsCnt = CountSymbols();  

    char *buffer = CopyToArr(fp, SymbolsCnt);

    OddSpaceRemoveArray(buffer);

    int size = CountString(buffer);
    
    Strings *arr = FillInStruct(buffer, size);


    qsort(arr, size, sizeof(struct Strings), Compare);
 
    PrintStrings(arr, size);
    free(arr);

}