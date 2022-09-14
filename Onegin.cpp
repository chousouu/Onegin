#include "Onegin.h"

void OddSpaceRemoveArray(char *buffer)
{
    char c = 0; 
    int check = 0;
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
}

char *ReadToBuffer(FILE *fp, int size) //readtobuffer
{
    char *buffer = (char *)calloc(size, sizeof(char));

    int PutZero = fread(buffer, sizeof(char), size, fp);
    buffer[PutZero] = '\0';

    return buffer;
}

int AnalyzeInput(int argcount, const char **argument, struct Input *info)
{
    int check = 0;
    info->mode = 0; // normal sort
    for (int i = 1; i < argcount; i++)
    {
        if(strncmp("-i", argument[i], 2) == 0)
        {
            info->inputfile = argument[i + 1];
            check++;
        }
        if(strncmp("-o", argument[i], 2) == 0)
        {
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

char *OpenFile(const char *name)
{
    FILE *fp = fopen(name, "r");
    if(fp == NULL)
    {
        printf("Could not open the file \"%s.txt\"\n", name);
    }
    return ReadToBuffer(fp, CountSymbols(name));
}

Strings *FillInStruct(char *buffer, int size)
{
    struct Strings * arr = (struct Strings *)calloc(size, sizeof(struct Strings)); 

    GetString(buffer, arr, size);

    return arr;
}

int CountSymbols(const char *name)
{
    struct stat buff;
    stat(name, &buff);
    
    return buff.st_size; 
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
        news++;
        arr[i].size = strlen(arr[i].string);
    }
}

int CountString(char *buffer)
{
    int count = 0;
    for(int i = 0; *(buffer + i) != '\0'; i++) 
    {
        if(buffer[i] == '\n')
        {
            count++;
        }
    }

    return count; 
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

int CompareFromEnd(struct Strings *z1, struct Strings *z2)
{
    for(int i = z1->size, j = z2->size; i >= 0 && j >= 0; i--, j--)
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
            return char1 - char2;
        }  
    }  
    return 0;
}

void swap(char *s1, char *s2)
{
    char * temp = s1; 
    s1 = s2;
    s2 = temp;
}

void quick_sort(struct Strings* p, int left, int right,  int (*CompareFromEnd)(struct Strings *z1, struct Strings *z2)) 
{
    int aaa = right - left;

    if(aaa == 2)
    {
        if(CompareFromEnd(&p[left], &p[left + 1]) < 0 )
        {
            swap(p[left].string, p[left + 1].string);
        }

        if(CompareFromEnd(&p[left + 1], &p[right]) < 0)
        {
            swap(p[left + 1].string, p[right].string);
        }
        if(CompareFromEnd(&p[left], &p[right]) < 0)
        {
            swap(p[left].string, p[right].string);
        }
    }
    else if(aaa == 1)
    {
        if(CompareFromEnd(&p[left], &p[right]) < 0)
        {
            swap(p[left].string, p[right].string);
        }
    }

    struct Strings *pivot = &p[(left + right) / 2];
    int i = left;   
    int j = right;

    while (i <= j) 
    {
        while(CompareFromEnd(&p[i], pivot) < 0) 
        {
            ++i;
        }
        while(CompareFromEnd(&p[j], pivot) > 0) 
        {
            --j;
        }
        if (i <= j) 
        {
            swap(p[i].string, p[j].string);
            ++i;
            --j;
        }
    }

    if (left < j) 
    {
        quick_sort(p, left, j, CompareFromEnd);
    }
    if (i < right) 
    {
        quick_sort(p, i, right, CompareFromEnd);
    }
}

int LowerCase(char c)
{
    if ((c >= 'A') && (c <= 'Z'))
    {
        return c + ('a' - 'A');    
    }
    if((c >= 'a') && (c <= 'z'))
    {
        return c;
    }
    else 
    {
        return -1;
    }
}

void PrintStrings(struct Strings *arr, int size, const char *name, int mode)
{
    FILE *fp = fopen(name, "w");
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
} // printstrings needs to receive file name; -> make func that opens in "W" / "r" mode file 