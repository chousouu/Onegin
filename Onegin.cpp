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
    for(int z = k + 1; z < i; z++) // put \0 on everything that we havent rewritten
    {
        buffer[z] = '\0';
    }
}

char *CopyToArr(FILE *fp, int size)
{
    char *buffer = (char *)calloc(size, sizeof(char));

    fp = OpenWriteFile("Hamlet.txt", "r");

    int PutZero = fread(buffer, sizeof(char), size, fp);
    buffer[PutZero] = '\0';

    return buffer;
}

FILE *OpenWriteFile(const char *name, const char *mode)
{
    FILE *fp = fopen(name, mode);
    if(fp == NULL)
    {
        printf("Could not open the file \"%s.txt\"", name);
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
        if(*(buffer + i) == '\n')
        {
            count++;
        }
    }

    return count; 
}

int Compare(const void *s1, const void *s2)
{
    int i = 0;
    int first_move = 0;
    int second_move = 0;
    const struct Strings *z1 = (const struct Strings *)s1;
    const struct Strings *z2 = (const struct Strings *)s2;
    while(1)
    {
        int char1 = LowerCase(*(z1->string + i + first_move)); 
        int char2 = LowerCase(*(z2->string + i + second_move));
        if(char1 == -1)
        {
            first_move++;
            continue;
        }
        if(char2 == -1)
        {
            second_move++;
            continue;
        }

        if(char1 == char2)
        {
            i++;
            continue;
        }

        if(char1 > char2)
        {
            return 1; 
        }
        else if(char1 < char2)
        {
            return -1;
        }
    }
}


void Merge(struct Strings *arr, int l, int m, int r) // merge sort 
{
    int nLeft = m - l + 1;
    int nRight = r - m;

    //printf("nLEFT RIGHT %d %d\n", nLeft, nRight);

    char *R[nRight];
    char *L[nLeft];

    for(int i = 0; i < nLeft; i++)
    {
        L[i] = arr[l + i].string;
        //printf("%d. %s\n", l + i, L[i]);
    }
    for(int j = 0; j < nRight; j++)
    {
        R[j] = arr[m + 1 + j].string;
      //  printf("%d.%s\n", m + 1 + j, R[j]);
    }

    int i = 0, j = 0, k = 0;

    
    while(i < nLeft && j < nRight)
    {
//        printf("%d\n", Compare(L[i], R[j]));

        if(Compare(L[i], R[j]) != -1)
        {
            arr[k].string = L[i];
            //printf("%s %s\n", arr[k].string, L[i]);
            i++;
        }
        else if(Compare(L[i], R[j]) == -1)
        {
            arr[k].string = R[j];
          //  printf("%s %s\n", arr[k].string, R[j]);
            j++;
        }
        k++;
    } 
  //  printf("ASDADASD\n");
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

       // printf("MSORT1\n");

        MSort(arr, m + 1, r);
        //printf("MSORT2\n");

       // printf("Merge l %d, m %d, r %d\n", l, m, r);
        Merge(arr, l, m, r);
     //   printf("MERGE\n");

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