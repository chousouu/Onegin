#ifndef ONEGIN_H
#define ONEGIN_H 

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <sys\stat.h>
#include <assert.h>

int CountString(char *buffer);
int CountSymbols(const char *name);
char *ReadToBuffer(FILE *fp, int size);//readtobuffer
void OddSpaceRemoveArray(char *buffer);
void GetString(char *buffer, struct Strings *arr, int size);
Strings *FillInStruct(char *buffer, int size);

int AnalyzeInput(int argcount, const char **argument, struct Input *info);
int LowerCase(char c);
int Compare(const void *s1, const void *s2);
int CompareFromEnd(struct Strings *z1, struct Strings *z2);
void quick_sort(struct Strings* p, int left, int right,  int (*CompareFromEnd)(struct Strings *z1, struct Strings *z2));
void PrintStrings(struct Strings *arr, int size, const char *name, int mode);
char *OpenFile(const char *name);

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