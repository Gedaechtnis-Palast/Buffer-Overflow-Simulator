#include "memoryMapping.h"

SEGMENT_COLLECTION stack;
SEGMENT_COLLECTION heap;
SEGMENT_COLLECTION staticMem;

SEGMENT createSegment(void *startAddress, void *endAddress, void *overflowEndAddress)
{
    printf("Segment: %p %lu %p\n", startAddress, (uintptr_t)startAddress);
    SEGMENT segment = {NULL, NULL, 0, 0, 0};
    if (startAddress != NULL) // TODO: error handling
    {
        segment.startAddress = (uintptr_t)startAddress;
    }
    if (endAddress != NULL)
    {
        segment.endAddress = (uintptr_t)endAddress;
    }
    if (overflowEndAddress != NULL)
    {
        segment.overflowEndAddress = (uintptr_t)overflowEndAddress;
    }
    return segment;
};

SEGMENT_COLLECTION createSegmentCollection(int initialSegmentCapacity)
{
    SEGMENT_COLLECTION collection = {
        NULL,
        0,
        0,
        0,
        initialSegmentCapacity};
    return collection;
};

bool initMemoryMap()
{
    stack = createSegmentCollection(20);
    heap = createSegmentCollection(20);
    staticMem = createSegmentCollection(20);
};

void printMemoryMap()
{
    SEGMENT currentSegment = *stack.startSegmentAddress;
    printf("start %lu current %lu diff %lu", stack.startAddress, currentSegment.startAddress, currentSegment.startAddress - stack.startAddress);
    for (unsigned long i = 0; i < stack.mappedSegments; i++)
    {
        unsigned long fillerDiff = currentSegment.startAddress - stack.startAddress;
        printf("\nf %lu", fillerDiff / 8);
        for (unsigned long filler = 0; filler < fillerDiff; filler++)
        {
            printf("%s.", WHITE);
            return;
        }
        unsigned long memoryDiff = currentSegment.endAddress - currentSegment.startAddress;
        printf("%lu", memoryDiff);
        for (unsigned long memSpace = 0; memSpace < memoryDiff; memSpace++)
        {
            printf("\nms %s\n:", GREEN);
            return;
        }
    }
    // get max and min from segment collection
    // get each segment from collection
    //
};

bool allocStack(void *startAddress, void *endAddress, void *overflowEndAddress, size_t dataTypeSize)
{
    return allocSegment(startAddress, endAddress, overflowEndAddress, dataTypeSize, &stack);
};
bool allocHeap(void *startAddress, void *endAddress, void *overflowEndAddress, size_t dataTypeSize)
{
    return allocSegment(startAddress, endAddress, overflowEndAddress, dataTypeSize, &heap);
};
bool allocStatic(void *startAddress, void *endAddress, void *overflowEndAddress, size_t dataTypeSize)
{
    return allocSegment(startAddress, endAddress, overflowEndAddress, dataTypeSize, &staticMem);
};

bool allocSegment(void *startAddress, void *endAddress, void *overflowEndAddress, size_t dataTypeSize, SEGMENT_COLLECTION *collection)
{
    SEGMENT newSegment = createSegment(startAddress, endAddress, overflowEndAddress);
    /**
     * Modify final size if necessary.
     */
    if (newSegment.startAddress != 0)
    {
        if (collection->startAddress == 0 || collection->startAddress > newSegment.startAddress)
        {
            collection->startAddress = newSegment.startAddress;
        }
        else if (collection->endAddress < newSegment.startAddress)
        {
            collection->endAddress = newSegment.startAddress + dataTypeSize;
        }
    }
    else
    {
        return false;
    }
    if (newSegment.endAddress != 0)
    {
        if (collection->endAddress < newSegment.endAddress)
        {
            collection->endAddress = newSegment.endAddress + dataTypeSize;
        }
    }
    if (newSegment.overflowEndAddress != 0)
    {
        if (collection->endAddress < newSegment.overflowEndAddress)
        {
            collection->endAddress = newSegment.overflowEndAddress + dataTypeSize;
        }
    }
    /**
     * Add segment into linked list sorted by address position.
     */
    if (collection->startSegmentAddress == NULL)
    {
        // printf("Before:%p %lu %lu\n", collection->startSegmentAddress, collection->mappedSegments, collection->startAddress);
        collection->startSegmentAddress = &newSegment;
        collection->mappedSegments++;
        // printf("After:%p %lu %lu\n", collection->startSegmentAddress, collection->mappedSegments, collection->startAddress);
    }
    else
    {
        SEGMENT *oldSegmentAddress = collection->startSegmentAddress;
        if ((*oldSegmentAddress).startAddress > newSegment.startAddress)
        {
            newSegment.next = oldSegmentAddress;
            if ((*oldSegmentAddress).previous == NULL)
            {
                collection->startSegmentAddress = &newSegment;
                (*oldSegmentAddress).previous = &newSegment;
            }
            else
            {
                newSegment.previous = oldSegmentAddress->previous;
                newSegment.next = oldSegmentAddress;

                oldSegmentAddress->previous = &newSegment;

                newSegment.previous->next = &newSegment;
            }
        }
    }
    return true;
};
