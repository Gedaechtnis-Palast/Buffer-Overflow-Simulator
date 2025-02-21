#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
} TYPE;

int allocHeap(bool isArray, int allocatedSize, TYPE dataType);
int allocStack(bool isArray, int allocatedSize);
int allocStatic(bool isArray, int allocatedSize);