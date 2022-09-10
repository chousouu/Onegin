#ifndef ONEGIN_H
#define ONEGIN_H 

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int CountString(char *buffer);
int CountSymbols(FILE *fw);
void SpaceRemoveAndCopyToArr(char* buffer, FILE *fp);
void GetString(char *buffer, struct Strings *arr, int size);

int LowerCase(char c);
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