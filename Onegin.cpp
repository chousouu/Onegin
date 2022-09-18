#include "Onegin.h"
int ParseArguments(int argcount, const char **argument, struct Input *info)
{
    int check = 0;
    info->mode = 0; // normal sort
    for (int i = 1; i < argcount; i++)
    {
        if(strncmp("-i", argument[i], 2) == 0)
        {
            if(strncmp("-o", argument[i + 1], 2) == 0)
            {
                printf("You cannot have %s as input file name!\n", argument[i + 1]);
                return check;
            }
            info->inputfile = argument[i + 1];
            check++;
        }
        if(strncmp("-o", argument[i], 2) == 0)
        {
            if(strncmp("-i", argument[i + 1], 2) == 0)
            {
                printf("You cannot have %s as output file name!\n", argument[i + 1]);
                return check;
            }
            info->outputfile = argument[i + 1];
            check++;
        }
        if(strncmp("-r", argument[i], 2) == 0)
        {
            info->mode = 1;
        }
    }
    return check;
}

void OddSpaceRemoveArray(char *buffer)
{
    char c = 0;
    int check = 1;
    int i = 0; //for before array
    int k = 0; // counter for after array

    while((c = buffer[i++]) != '\0')
    {
        if(c == '\n' && check == 0)
        {
            buffer[k] = c;
            k++;
            check = 1;
        }
        else if(c == '\n' && check == 1)
        {
            continue;
        }
        else if(c != '\n')
        {
            if (check == 1 && c == ' ')
            {
                continue;
            }
            else
            {
                buffer[k] = c;
                k++;
                check = 0;
            }
        }
    }

    buffer[k] = '\n';
    buffer[k + 1] = '\0';


}

char *ReadToBuffer(FILE *fp, int size)
{
    char *buffer = (char *)calloc(size, sizeof(char));

    int PutZero = fread(buffer, sizeof(char), size, fp);
    buffer[PutZero] = '\0';

    return buffer;
}

void GetString(char *buffer, struct Strings *arr, int size)
{
    char *news = buffer;
    char *old = NULL;
    for(int i = 0; i < size; i++)
    {
        arr[i].string = news;
        news = strchr(news, '\n');
        *news = '\0';
        arr[i].size = strlen(arr[i].string);
        news++;
    }
}

int CountSymbols(const char *name)
{
    struct stat buff = {};
    stat(name, &buff);

    return buff.st_size;
}

int CountString(char *buffer)
{
    int count = 0;

    for(int i = 0; buffer[i] != '\0'; i++)
    {
        if(buffer[i] == '\n')
        {
            count++;
        }
    }
    return count;
}

Strings *FillInStruct(char *buffer, int size)
{
    struct Strings * arr = (struct Strings *)calloc(size, sizeof(struct Strings));

    GetString(buffer, arr, size);

    return arr;
}

int Compare(const void *s1, const void *s2)
{
    const struct Strings *z1 = (const struct Strings *)s1;
    const struct Strings *z2 = (const struct Strings *)s2;

    for(int i = 0, j = 0; i <= z1->size && j <= z2->size; i++, j++)
    {
        while(!isalpha(z1->string[i]))
        {
            i++;
        }
        while(!isalpha(z2->string[j]))
        {
            j++;
        }

        int char1 = LowerCase(z1->string[i]);
        int char2 = LowerCase(z2->string[j]);
        int razn = char1 - char2;

        if(razn)
        {
            return char1 - char2;
        }
    }
    return 0;
}

int CompareFromEnd(const void *s1, const void *s2)
{
    const struct Strings *z1 = (const struct Strings *)s1;
    const struct Strings *z2 = (const struct Strings *)s2;

    for(int i = (z1->size - 1), j = (z2->size - 1); i >= 0 && j >= 0; i--, j--)
    {
        while(!isalpha(z1->string[i]))
        {
            i--;
        }
        while(!isalpha(z2->string[j]))
        {
            j--;
        }

        int char1 = LowerCase(z1->string[i]);
        int char2 = LowerCase(z2->string[j]);
        int razn = char1 - char2;

        if(razn)
        {
            return razn;
        }
    }
    return 0;
}

void bubblesort(struct Strings* p, int sizeofArray, int size, int (*Comp)(const void *z1, const void *z2))
{
    for(int i = 0; i < size - 1; i++)
    {
        for(int j = 0; j < size - i - 1; j++)
        {
            if(Comp(p + j, p + (j + 1) ) > 0)
            {
                SwapStruct(p + j, p + (j + 1));
            }
        }
    }
}

void QuickSort(struct Strings* p, int left, int right, int (*Compare)(const void *z1, const void *z2))
{
    struct Strings *pivot = &p[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j)
    {
        while(Compare(p + i, pivot) < 0)
        {
            ++i;
        }
        while(Compare(p + j, pivot) > 0)
        {
            --j;
        }
        if (i <= j)
        {
            SwapStruct(p + i, p + j);
            ++i;
            --j;
        }
    }

    if (left <= j)
    {
        QuickSort(p, left, j, Compare);
    }
    if (i <= right)
    {
        QuickSort(p, i, right, Compare);
    }
}

void SwapString(struct Strings *s1, struct Strings *s2)
{
    struct Strings temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

char LowerCase(char c)
{
    if ((c >= 'A') && (c <= 'Z'))
    {
        return c + ('a' - 'A');
    }

    return c;
}

void PrintStrings(struct Strings *arr, int size, const char *name, int mode)
{
    FILE *fp = fopen(name, "w");
    if(fp == NULL)
    {
        printf("Could not open the file \"%s.txt\"\n", name);
        return;
    }

    if(mode)
    {
        for(int i = 0; i < size; i++)
        {
            fprintf(fp, "%60s\n", arr[i].string);
        }
    }
    else
    {
        for(int i = 0; i < size; i++)
        {
            fprintf(fp, "%s\n", arr[i].string);
        }
    }

    fclose(fp);
    return;
}

char *OpenFile(const char *name)
{
    FILE *fp = fopen(name, "r");
    if(fp == NULL)
    {
        printf("Could not open the file \"%s\"\n", name);
        return NULL; 
    }
    return ReadToBuffer(fp, CountSymbols(name));
}

void FreeMemory(struct Strings *arr)
{
    free(arr->string);
    free(arr);
}
