#ifndef ONEGIN_H
#define ONEGIN_H 

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <sys\stat.h>

int AnalyzeInput(int argcount, const char **argument, struct Input *info);
void OddSpaceRemoveArray(char *buffer);
char *ReadToBuffer(FILE *fp, int size);
void GetString(char *buffer, struct Strings *arr, int size);
int CountSymbols(const char *name);
int CountString(char *buffer);
Strings *FillInStruct(char *buffer, int size);
int Compare(const void *s1, const void *s2);
int CompareFromEnd(const void *s1, const void *s2);
void bubblesort(struct Strings* p, int sizeofArray, int size, int (*Comp)(const void *z1, const void *z2));
void quick_sort(struct Strings* p, int left, int right,  int (*CompareFromEnd)(const void *z1, const void *z2)); 
void swap(struct Strings *s1, struct Strings *s2);
int LowerCase(char c);
void PrintStrings(struct Strings *arr, int size, const char *name, int mode);
char *OpenFile(const char *name);
void FreeMemory(struct Strings *arr);

struct Strings 
{
    char *string;
    int size;
};

struct Input
{
    const char *inputfile;
    const char *outputfile;
    int mode; // 0 - normal ; 1 - reverse comp
};

#endif//ONEGIN_H