#include "memoryMapping.h"

SEGMENT_COLLECTION stack;
SEGMENT_COLLECTION heap;
SEGMENT_COLLECTION staticMem;

SEGMENT *createSegment(void *startAddress, void *endAddress, void *overflowEndAddress)
{
    SEGMENT *segment = (SEGMENT *)malloc(sizeof(SEGMENT));
    if (!segment)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    if (startAddress != NULL)
        segment->startAddress = (uintptr_t)startAddress;
    else
        segment->startAddress = 0;

    if (endAddress != 0)
        segment->endAddress = (uintptr_t)endAddress;
    else
        segment->endAddress = 0;

    if (overflowEndAddress != NULL)
        segment->overflowEndAddress = (uintptr_t)overflowEndAddress;
    else
        segment->overflowEndAddress = 0;

    segment->next = NULL;
    segment->previous = NULL;

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
    return (&stack != NULL && &heap != NULL && &staticMem != NULL);
};

void printMemoryMap()
{
    printf("[stack]\n");
    printSegmentCollection(&stack);
    printf("[heap]\n");
    printSegmentCollection(&heap);
    printf("[static]\n");
    printSegmentCollection(&staticMem);
};

void printSegmentCollection(SEGMENT_COLLECTION *collection)
{
    SEGMENT *currentSegment = collection->startSegmentAddress;
    for (unsigned long i = 0; i < collection->mappedSegments; i++)
    {
        unsigned long fillerDiff = currentSegment->startAddress - collection->startAddress;
        for (unsigned long filler = 0; filler < fillerDiff; filler++)
        {
            printf("%s|", WHITE);
        }
        unsigned long memoryDiff = currentSegment->endAddress - currentSegment->startAddress;
        for (unsigned long ms = 0; ms < memoryDiff; ms++)
        {
            printf("%s|", GREEN);
        }
        if (currentSegment->overflowEndAddress != 0)
        {
            unsigned long overflowDiff = currentSegment->overflowEndAddress - currentSegment->endAddress;
            for (unsigned long os = 0; os < overflowDiff; os++)
            {
                printf("%s|", RED);
            }
        }
        currentSegment = currentSegment->next;
    }
    printf("\n");
}

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
    SEGMENT *newSegment = createSegment(startAddress, endAddress, overflowEndAddress);
    /**
     * Modify final size if necessary.
     */
    if (newSegment->startAddress != 0)
    {
        if (collection->startAddress == 0 || collection->startAddress > newSegment->startAddress)
        {
            collection->startAddress = newSegment->startAddress;
        }
        else if (collection->endAddress < newSegment->startAddress)
        {
            collection->endAddress = newSegment->startAddress + dataTypeSize;
        }
    }
    else
    {
        return false;
    }
    if (newSegment->endAddress == 0)
    {
        newSegment->endAddress = newSegment->startAddress + dataTypeSize;
    }
    if (collection->endAddress < newSegment->endAddress)
    {
        collection->endAddress = newSegment->endAddress + dataTypeSize;
    }
    if (newSegment->overflowEndAddress != 0)
    {
        if (collection->endAddress < newSegment->overflowEndAddress)
        {
            collection->endAddress = newSegment->overflowEndAddress + dataTypeSize;
        }
    }
    /**
     * Add segment into linked list sorted by address position.
     */
    if (collection->startSegmentAddress == NULL)
    {
        collection->startSegmentAddress = newSegment;
        collection->mappedSegments++;
    }
    else
    {
        SEGMENT *listedSegmentAddress = collection->startSegmentAddress;
        while (1)
        {
            if ((*listedSegmentAddress).startAddress > newSegment->startAddress)
            {
                newSegment->next = listedSegmentAddress;
                if ((*listedSegmentAddress).previous == NULL)
                {
                    collection->startSegmentAddress = newSegment;
                    (*listedSegmentAddress).previous = newSegment;
                    collection->mappedSegments++;
                    break;
                }
                else
                {
                    newSegment->previous = listedSegmentAddress->previous;
                    newSegment->next = listedSegmentAddress;

                    listedSegmentAddress->previous = newSegment;

                    newSegment->previous->next = newSegment;
                    collection->mappedSegments++;
                    break;
                }
            }
            else
            {
                if (listedSegmentAddress->next == NULL)
                {
                    listedSegmentAddress->next = newSegment;
                    newSegment->previous = listedSegmentAddress;
                    collection->mappedSegments++;
                    break;
                }
                else
                {
                    listedSegmentAddress = listedSegmentAddress->next;
                }
            }
        }
    }
    return true;
};

bool freeSegment(void *address)
{
    if (freeMemory(address, &stack))
    {
        return true;
    }
    // if (freeMemory(address, &heap))
    // {
    //     return true;
    // }
    // if (freeMemory(address, &staticMem))
    // {
    //     return true;
    // }
}

bool freeMemory(void *address, SEGMENT_COLLECTION *collection)
{
    unsigned long addressValue = (uintptr_t)address;
    bool notFreed = true;
    SEGMENT *start = collection->startSegmentAddress;
    while (notFreed && start != NULL)
    {
        if (collection->startSegmentAddress->startAddress == addressValue)
        {
            collection->startSegmentAddress = collection->startSegmentAddress->next;
            free((void *)start);
            notFreed = false;
        }
        else if (start->startAddress == addressValue)
        {
            start->previous->next = start->next;
            start->next->previous = start->previous;
            free((void *)start);
            int *test = (int *)malloc(sizeof(int));
            printf("%p\n", test);
            free((void *)test);
            printf("%p\n", test);
            notFreed = false;
        }
        else
        {
            start = start->next;
        }
    }
    return !notFreed;
}