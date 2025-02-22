#include "memoryMapping.h"

SEGMENT_COLLECTION stack;
SEGMENT_COLLECTION heap;
SEGMENT_COLLECTION staticMem;

SEGMENT createSegment(void *startAddress, void *endAddress, void *overflowEndAddress)
{
    SEGMENT segment = {0, 0, 0};
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
        (SEGMENT *)malloc(initialSegmentCapacity * sizeof(SEGMENT)), // TODO: error handling
        {0, 0, 0},
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

void printMemoryMap() {
    // get max and min from segment collection
    // get each segment from collection
    //
};

bool allocStack(void *startAddress, void *endAddress, void *overflowEndAddress, size_t dataTypeSize)
{
    return allocSegment(startAddress, endAddress, overflowEndAddress, dataTypeSize, stack);
};
bool allocHeap(void *startAddress, void *endAddress, void *overflowEndAddress, size_t dataTypeSize)
{
    return allocSegment(startAddress, endAddress, overflowEndAddress, dataTypeSize, heap);
};
bool allocStatic(void *startAddress, void *endAddress, void *overflowEndAddress, size_t dataTypeSize)
{
    return allocSegment(startAddress, endAddress, overflowEndAddress, dataTypeSize, staticMem);
};

bool allocSegment(void *startAddress, void *endAddress, void *overflowEndAddress, size_t dataTypeSize, SEGMENT_COLLECTION collection)
{
    SEGMENT newSegment = createSegment(startAddress, endAddress, overflowEndAddress);
    if (newSegment.startAddress != NULL)
    {
        if (collection.finalSize.startAddress > newSegment.startAddress)
        {
            collection.finalSize.startAddress = newSegment.startAddress;
        }
        else if (collection.finalSize.endAddress < newSegment.startAddress)
        {
            collection.finalSize.endAddress = newSegment.startAddress + dataTypeSize;
        }
    }
    else
    {
        return false;
    }
    if (newSegment.endAddress != NULL)
    {
        if (collection.finalSize.endAddress < newSegment.endAddress)
        {
            collection.finalSize.endAddress = newSegment.endAddress + dataTypeSize;
        }
    }
    if (newSegment.overflowEndAddress != NULL)
    {
        if (collection.finalSize.endAddress < newSegment.overflowEndAddress)
        {
            collection.finalSize.endAddress = newSegment.overflowEndAddress + dataTypeSize;
        }
    }
    return true;
};
