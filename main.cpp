#include "Onegin.h"

int main(int argc, const char **argv) 
{ 
    struct Input info = 
    {
        NULL,
        NULL,
        0    
    }; 

    int count = AnalyzeInput(argc, argv, &info);

    if (count == 2)
    {
        char *buffer = OpenFile(info.inputfile);
        OddSpaceRemoveArray(buffer);

        int size = CountString(buffer);
        Strings *arr = FillInStruct(buffer, size);
        
        if(info.mode == 0)
        {
            qsort(arr, size, sizeof(struct Strings), Compare);
        }
        else 
        {
            qsort(arr, size, sizeof(struct Strings), CompareFromEnd);
        }

        PrintStrings(arr, size, info.outputfile, info.mode);
    }
    else 
    {
        if(info.inputfile == NULL)
        {
            printf("Put -i filename.txt\n");
        }
        if(info.outputfile == NULL)
        {
            printf("Put -o filename.txt\n");
        }
    }
}