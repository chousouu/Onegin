#include "Onegin.h"

void SpaceRemoveAndCopyToArr(char* buffer, FILE *fp)
{
    rewind(fp);
    int c = 0; 
    int check = 0;
    int i = 0;

    while((c = fgetc(fp)) != EOF)
    {
        if(c == '\n' && check == 0)
        {
            *(buffer + i) = c;
            i++;
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
                *(buffer + i) = c;
                i++;
                check = 0;
            }
        }
    }
    *(buffer + i) = '\n';
    *(buffer + i + 1) = '\0';
    rewind(fp);
       
}

int CountSymbols(FILE *fw)
{
    fseek(fw, 0, SEEK_END);
    
    return (int)ftell(fw); 
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

int Compare(char *s1, char *s2)
{
    int i = 0;
    
    while(s1[i]!= '\0' && s2[i] != '\0')
    {
        char char1 = LowerCase(s1[i]);
        char char2 = LowerCase(s2[i]);

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

    int sizes1 = strlen(s1);
    int sizes2 = strlen(s2);

    if(sizes1 > sizes2)
    {
        return 1;
    } 
    else if (sizes1 < sizes2)
    {
        return -1;
    }
    else 
    {
        return 0; //odinakovie stroki
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
        printf("%d. %s\n", l + i, L[i]);
    }
    for(int j = 0; j < nRight; j++)
    {
        R[j] = arr[m + 1 + j].string;
        printf("%d.%s\n", m + 1 + j, R[j]);
    }

    printf("FILLED\n");
    int i = 0, j = 0, k = 0;

    
    while(i < nLeft && j < nRight)
    {
        printf("%d\n", Compare(L[i], R[j]));

        if(Compare(L[i], R[j]) != -1)
        {
            arr[k].string = L[i];
            printf("%s %s\n", arr[k].string, L[i]);
            i++;
        }
        else if(Compare(L[i], R[j]) == -1)
        {
            arr[k].string = R[j];
            printf("%s %s\n", arr[k].string, R[j]);
            j++;
        }
        k++;
    } 
    printf("ASDADASD\n");
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

        printf("MSORT1\n");

        MSort(arr, m + 1, r);
        printf("MSORT2\n");

        printf("Merge l %d, m %d, r %d\n", l, m, r);
        Merge(arr, l, m, r);
        printf("MERGE\n");

    }
}

int LowerCase(char c)
{
    if ((c >= 'A') && (c <= 'Z'))
    {
        return c + ('a' - 'A');    
    }
    return c;
}

void PrintStrings(struct Strings *arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%s", arr[i].string);
    }
}