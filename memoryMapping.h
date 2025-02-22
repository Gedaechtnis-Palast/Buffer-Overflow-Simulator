#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"

typedef struct SEGMENT
{
    struct SEGMENT *next;
    struct SEGMENT *previous;
    unsigned long startAddress;
    unsigned long endAddress;
    unsigned long overflowEndAddress;
} SEGMENT;

typedef struct
{
    SEGMENT *startSegmentAddress;
    unsigned long startAddress;
    unsigned long endAddress;
    int mappedSegments;
    int segmentCapacity;

} SEGMENT_COLLECTION;

/**
 * Creates a SEGMENT, which represents data stored in the memory.
 */
SEGMENT createSegment(void *startAddress, void *endAddress, void *overflowEndAddress);
/**
 * Creates a SEGMENT_COLLECTION, which represents either the heap, stack or static areas in memory.
 */
SEGMENT_COLLECTION createSegmentCollection(int initialSegmentCapacity);
/**
 * Initialization of internal memory mapping for a console visualization.
 */
bool initMemoryMap();
void printMemoryMap();

/**
 * Accepts the start and end address of a variable to map for the memory visualization.
 * Optionally an extra address can be passed to indicate an overflow reaching over the end address.
 * @startAddress the pointer to a variable. (required)
 * @endAddress the pointer to the last allocated cell of an array. (optional)
 * @overflowEndAddress the address indicating the reach of the overflow over the endAddress. (optional)
 */
bool allocStack(void *startAddress, void *endAddress, void *overflowEndAddress, size_t dataTypeSize);
/**
 * Accepts the start and end address of a variable to map for the memory visualization.
 * Optionally an extra address can be passed to indicate an overflow reaching over the end address.
 * @startAddress the pointer to a variable. (required)
 * @endAddress the pointer to the last allocated cell of an array. (optional)
 * @overflowEndAddress the address indicating the reach of the overflow over the endAddress. (optional)
 */
bool allocHeap(void *startAddress, void *endAddress, void *overflowEndAddress, size_t dataTypeSize);
/**
 * Accepts the start and end address of a variable to map for the memory visualization.
 * Optionally an extra address can be passed to indicate an overflow reaching over the end address.
 * @startAddress the pointer to a variable. (required)
 * @endAddress the pointer to the last allocated cell of an array. (optional)
 * @overflowEndAddress the address indicating the reach of the overflow over the endAddress. (optional)
 */
bool allocStatic(void *startAddress, void *endAddress, void *overflowEndAddress, size_t dataTypeSize);

bool allocSegment(void *startAddress, void *endAddress, void *overflowEndAddress, size_t dataTypeSize, SEGMENT_COLLECTION *collection);