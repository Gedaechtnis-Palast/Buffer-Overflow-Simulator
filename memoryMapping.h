#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    unsigned long startAddress;
    unsigned long endAddress;
    unsigned long overflowEndAddress;
} SEGMENT;

typedef struct
{
    SEGMENT array;
    SEGMENT finalSize;
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

bool allocSegment(void *startAddress, void *endAddress, void *overflowEndAddress, size_t dataTypeSize, SEGMENT_COLLECTION collection);