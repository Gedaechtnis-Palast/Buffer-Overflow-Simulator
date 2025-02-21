#include "loopiterator.h"

void loopIterator()
{
    int success = 0;
    while (!success)
    {
        INPUT input = getInput();
        char *iterations = (char *)(input.buffer + (int)(input.current_size / 2));
        /**
         * Get lowest four bits from first char and highest four bits of the next char.
         * The intersection simulates a buffer overflow impacting variables used for loops.
         */
        unsigned char shifted_iterations = ((iterations[0] & 0x0F) << 4) | ((iterations[1] & 0xF0) >> 4);

        for (int i = shifted_iterations; 179 <= i && 240 >= i; i++)
        {
            success = 1;
            printf("Successfully entered the loop!\n");
        }
    }
}