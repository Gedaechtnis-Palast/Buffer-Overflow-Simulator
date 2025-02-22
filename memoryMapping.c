#include "memoryMapping.h"

int allocHeap(void *startAddress, void *endAddress, void *overflowEndAddress)
{
    int test = 1;
    printf("pointer print: %p\n", &test);
    char pointerChars[100] = (char)&test;
    printf("pointer chars print: %s", pointerChars);
    return 0;
};
int allocStack(void *startAddress, void *endAddress, void *overflowEndAddress)
{
    return 0;
};
int allocStatic(void *startAddress, void *endAddress, void *overflowEndAddress)
{
    return 0;
};