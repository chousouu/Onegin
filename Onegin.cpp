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

char *CopyToArr(FILE *fp, int size)
{
    char *buffer = (char *)calloc(size, sizeof(char));

    int PutZero = fread(buffer, sizeof(char), size, fp);
    buffer[PutZero] = '\0';

    return buffer;
}

FILE *OpenFile()
{
    char name[50]; 
    printf("Write the file name you want to sort(Don't forget to put .txt at the end): ");
    scanf("%s", name);

    FILE *fp = fopen(name, "r");
    if(fp == NULL)
    {
        printf("Could not open the file \"%s.txt\"\n", name);
    }
    return fp;
}

Strings *FillInStruct(char *buffer, int size)
{
    struct Strings * arr = (struct Strings *)calloc(size, sizeof(struct Strings)); 

    GetString(buffer, arr, size);

    return arr;
}

int CountSymbols()
{
    struct stat buff;
    stat("Hamlet.txt", &buff);
    
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
    for(int i = 0, j = 0, k = 0; (i + j) < z1->size && (i + k) < z2->size; i++)
    {
        int char1 = LowerCase(z1->string[i + j]); 
        int char2 = LowerCase(z2->string[i + k]);
        if(char1 == -1)
        {
            j++;
            continue;
        }
        if(char2 == -1)
        {
            k++;
            continue;
        }

        int razn = char1 - char2;
        if(razn == 0)
        {
            continue;
        }
        else if(razn > 0)
        {
            return 1; 
        }
        else 
        {
            return -1;
        }
    }
    if(z1->size > z2->size)
    {
        return 1;
    }
    else if(z1->size < z2->size)
    {
        return -1;
    }
    else 
    {
        return 0;
    }
}


void Merge(struct Strings *arr, int l, int m, int r) // merge sort 
{
    int nLeft = m - l + 1;
    int nRight = r - m;


    char *R[nRight];
    char *L[nLeft];

    for(int i = 0; i < nLeft; i++)
    {
        L[i] = arr[l + i].string;
    }
    for(int j = 0; j < nRight; j++)
    {
        R[j] = arr[m + 1 + j].string;
    }

    int i = 0, j = 0, k = 0;

    
    while(i < nLeft && j < nRight)
    {

        if(Compare(L[i], R[j]) != -1)
        {
            arr[k].string = L[i];
            i++;
        }
        else if(Compare(L[i], R[j]) == -1)
        {
            arr[k].string = R[j];
            j++;
        }
        k++;
    } 
    while(i < nLeft)
    {
        arr[k].string = L[i];
        i++;
        k++;
    }
    while(j < nRight)
    {
        arr[k].string = R[j];
        j++;
        k++;
    }
}

void MSort(struct Strings *arr, int l, int r)
{   
    if(l < r)
    {
        int m = l + (r - l) / 2;
        
        MSort(arr, l, m);


        MSort(arr, m + 1, r);

        Merge(arr, l, m, r);

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

void PrintStrings(struct Strings *arr, int size)
{
    FILE *fp = fopen("Hamlet2.txt", "w");
    for(int i = 0; i < size; i++)
    {
        fwrite(arr[i].string, sizeof(char), arr[i].size, fp);
        fputc('\n', fp);    
    }
    fclose(fp);
} // printstrings needs to receive file name; -> make func that opens in "W" / "r" mode file 