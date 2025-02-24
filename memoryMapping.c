#include "memoryMapping.h"

/**
 * for local variables with short timespan
 */
SEGMENT_COLLECTION stack;
/**
 * for variables created with malloc or realloc
 */
SEGMENT_COLLECTION heap;
/**
 * for static variables or direct string definitions
 * e.g. (char *string = "this is a direct string definition")
 */
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

SEGMENT_COLLECTION createSegmentCollection()
{
    SEGMENT_COLLECTION collection = {
        NULL,
        0,
        0,
        0};
    return collection;
};

bool initMemoryMap()
{
    stack = createSegmentCollection();
    heap = createSegmentCollection();
    staticMem = createSegmentCollection();
    return (&stack != NULL && &heap != NULL && &staticMem != NULL);
};

void printMemoryMap()
{
    printf("\n[stack]\n(size:%d)\n", stack.endAddress - stack.startAddress);
    printSegmentCollection(&stack);
    printf("[heap]\n(size:%d)\n", heap.endAddress - heap.startAddress);
    printSegmentCollection(&heap);
    printf("[static]\n(size:%d)\n", staticMem.endAddress - staticMem.startAddress);
    printSegmentCollection(&staticMem);
};

void printSegmentCollection(SEGMENT_COLLECTION *collection)
{
    if (collection->startSegmentAddress == NULL)
    {
        printf("-NO MEMORY USED-\n");
        return;
    }

    SEGMENT *currentSegment = collection->startSegmentAddress;
    unsigned long previousAddress = collection->startSegmentAddress->startAddress;
    for (unsigned long i = 0; i < collection->mappedSegments; i++)
    {
        unsigned long fillerDiff = currentSegment->startAddress - previousAddress;
        if (fillerDiff > 100)
        {
            printf("%s||||||||||%s-[%d-addresses-truncated]-%s||||||||||", WHITE, YELLOW, fillerDiff - 20, WHITE);
        }
        else
        {
            for (unsigned long filler = 0; filler < fillerDiff; filler++)
            {
                printf("%s|", WHITE);
            }
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
        previousAddress = currentSegment->startAddress;
        currentSegment = currentSegment->next;
    }
    printf("%s\n", NORMAL);
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
        collection->endAddress = newSegment->endAddress;
    }
    if (newSegment->overflowEndAddress != 0)
    {
        if (collection->endAddress < newSegment->overflowEndAddress)
        {
            collection->endAddress = newSegment->overflowEndAddress;
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
            if (listedSegmentAddress->startAddress > newSegment->startAddress)
            {
                newSegment->next = listedSegmentAddress;
                if (listedSegmentAddress->previous == NULL)
                {
                    collection->startSegmentAddress = newSegment;
                    listedSegmentAddress->previous = newSegment;
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
    if (freeMemory(address, &heap))
    {
        return true;
    }
    if (freeMemory(address, &staticMem))
    {
        return true;
    }
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
            if (collection->startSegmentAddress != NULL)
            {
                collection->startAddress = collection->startSegmentAddress->startAddress;
            }
            else
            {
                collection->startAddress = 0;
                collection->endAddress = 0;
            }
            free((void *)start);
            collection->mappedSegments--;
            notFreed = false;
        }
        else if (start->startAddress == addressValue)
        {
            start->previous->next = start->next;
            if (start->next == NULL)
            {
                collection->endAddress = start->previous->endAddress;
            }
            else
            {
                start->next->previous = start->previous;
            }
            free((void *)start);
            collection->mappedSegments--;
            notFreed = false;
        }
        else
        {
            start = start->next;
        }
    }
    return !notFreed;
}

/*
    int test = 1234;
    double array[255] = {1, 2, 3, 4, 5};
    char test2 = 'a';

    initMemoryMap();
    allocStack((void *)&test, NULL, NULL, sizeof(int));
    allocHeap((void *)(&array[0]), (void *)(&array[100]), (void *)(&array[254]), sizeof(int));
    allocStatic((void *)&test2, NULL, NULL, sizeof(char));
    printMemoryMap();
    freeSegment((void *)&test);
    freeSegment((void *)&test2);
    freeSegment((void *)array);
    printMemoryMap();
*/