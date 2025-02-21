#include <stdbool.h>

typedef enum
{
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
} TYPE;
/**
 * Takes the address of a value to map, alongside the information:
 * - if it is an array
 * - allocated size in memory
 * - the size it is allowed to have (buffer overflows normally do go beyond this value)
 * - the type
 */
int allocHeap(void *startAddress, bool isArray, int allocatedSize, int allowedSize, TYPE dataType);
int allocStack(void *startAddress, bool isArray, int allocatedSize, int allowedSize, TYPE dataType);
int allocStatic(void *startAddress, bool isArray, int allocatedSize, int allowedSize, TYPE dataType);