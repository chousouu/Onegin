#ifndef ONEGIN_H
#define ONEGIN_H 

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys\stat.h>
#include <assert.h>

int CountString(char *buffer);
int CountSymbols();
char *CopyToArr(FILE *fp, int size);
void OddSpaceRemoveArray(char *buffer);
void GetString(char *buffer, struct Strings *arr, int size);
Strings *FillInStruct(char *buffer, int size);

int LowerCase(char c);
int Compare(const void *s1, const void *s2);
void MSort(struct Strings *arr, int l, int r);
void Merge(struct Strings *arr, int l, int m, int r);
void PrintStrings(struct Strings *arr, int size);
FILE *OpenFile();

struct Strings 
{
    char *string;
    int size;
};


#endif//ONEGIN_H