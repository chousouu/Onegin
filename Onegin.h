#ifndef ONEGIN_H
#define ONEGIN_H 

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys\stat.h>


int CountString(char *buffer);
int CountSymbols();
char * CopyToArr(FILE *fp, int size);
char *SpaceRemoveAndCopyToArr(int size, FILE *fp);
void GetString(char *buffer, struct Strings *arr, int size);
Strings *FillInStruct(char *buffer, int size);

char LowerCase(char c);
int Compare(char *s1, char *s2);
void MSort(struct Strings *arr, int l, int r) ;
void Merge(struct Strings *arr, int l, int m, int r);
void PrintStrings(struct Strings *arr, int size);

struct Strings 
{
    char *string;
    int size;
};


#endif//ONEGIN_H