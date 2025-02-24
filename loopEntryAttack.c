#include "loopEntryAttack.h"

void loopEntryAttack(char *fileBuffer, long fileBufferLength)
{
    INPUT *input;
    int success = 0;
    allocStack((void *)&success, NULL, NULL, sizeof(int));
    while (!success)
    {
        if (fileBuffer == NULL || fileBufferLength == 0)
        {
            input = getInput(DEFAULT_CAPACITY);
        }
        else
        {
            success = 1; // force while loop to stop after first iteration
            input = (INPUT *)malloc(sizeof(INPUT));
            input->buffer = fileBuffer;
            input->current_size = fileBufferLength;
            input->capacity = fileBufferLength + 1;
        }
        allocHeap(input, NULL, NULL, sizeof(INPUT));
        allocHeapBuffer(input);
        if (input->current_size > DEFAULT_CAPACITY)
        {
            char *iterations = input->buffer + DEFAULT_CAPACITY + (int)((input->current_size - DEFAULT_CAPACITY) / 2);
            allocHeap(iterations, NULL, NULL, sizeof(char));
            /**
             * Get lowest four bits from first char and highest four bits of the next char.
             * The intersection simulates a buffer overflow impacting variables used for loops.
             */
            unsigned char shifted_iterations = ((iterations[0] & 0x0F) << 4) | ((iterations[1] & 0xF0) >> 4);
            allocStack((void *)&shifted_iterations, NULL, NULL, sizeof(char));
            printMemoryMap(); // print after overflow is applied
            for (int i = shifted_iterations; 179 <= i && 240 >= i; i++)
            {
                success = 1;
                printf("Successfully entered the loop!\n");
            }
            freeSegment((void *)&success);
            freeSegment((void *)iterations);
            freeSegment((void *)&shifted_iterations);
        }
        freeSegment((void *)input->buffer);
        freeSegment((void *)input);
        free((void *)input->buffer);
        free((void *)input);
        printMemoryMap();
    }
}

bool allocHeapBuffer(INPUT *input)
{
    return allocHeap((void *)input->buffer,
                     (void *)(input->buffer + DEFAULT_CAPACITY - 1),
                     (input->current_size > DEFAULT_CAPACITY ? (void *)(input->buffer + (input->current_size)) : NULL),
                     sizeof(char));
}