#include "returnAddressAttack.h"
#include "loopEntryAttack.h"
#include "memoryMapping.h"

void returnAddressAttack(char *fileBuffer, long fileBufferLength, bool depSecurityActive)
{

    void *returnAddress = __builtin_return_address(0); // do not map this, it causes some flaky null pointers
    unsigned long returnAddressAddress = (uintptr_t)&returnAddress;
    int addressLength = digitCount(returnAddressAddress);
    char addressString[addressLength + 1];
    sprintf(addressString, "%lu", returnAddressAddress);
    allocStack(&returnAddressAddress, NULL, NULL, sizeof(unsigned long));
    allocStack(&addressLength, NULL, NULL, sizeof(int));
    allocStack(&addressString, &addressString[addressLength], NULL, sizeof(char));

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
            if (input->current_size <= DEFAULT_CAPACITY * 2)
            {
                for (int i = 0; i < addressLength; i++)
                {
                    printf(" _");
                }
                printf("\n");
            }
            else
            {
                int addressOverwrite = input->current_size - DEFAULT_CAPACITY * 2;
                allocStack(&addressOverwrite, NULL, NULL, sizeof(int));
                if (checkSuccess(addressString, addressLength, input->buffer, addressOverwrite))
                {
                    if (depSecurityActive)
                    {
                        printf("Yay you successfully overwrote the return address but DEP Security wont let you run your malicious code!");
                    }
                    else
                    {
                        printf("You successfully overwrote the return address to execute code from your buffer overflow!\n");
                    }
                    printMemoryMap();
                    freeSegment(&addressOverwrite);
                    freeSegment((void *)&success);
                    freeSegment((void *)input->buffer);
                    freeSegment((void *)input);
                    free((void *)input->buffer);
                    free((void *)input);
                    freeSegment((void *)&returnAddressAddress);
                    freeSegment((void *)&addressLength);
                    freeSegment((void *)&addressString);
                    return;
                }
                for (int i = 0; i < addressOverwrite && i < addressLength; i++)
                {
                    if (addressString[i] == input->buffer[DEFAULT_CAPACITY * 2 + i])
                        printf(" %c", addressString[i]);
                    else
                        printf(" x");
                }
                if (addressOverwrite < addressLength)
                {
                    for (int i = 0; i < addressLength - addressOverwrite; i++)
                    {
                        printf(" _");
                    }
                }
                printf("\n");
                printMemoryMap();
                freeSegment(&addressOverwrite);
            }
            freeSegment((void *)&success);
        }
        else
        {
            printMemoryMap();
        }
        freeSegment((void *)input->buffer);
        freeSegment((void *)input);
        free((void *)input->buffer);
        free((void *)input);
        printMemoryMap();
        if (success)
        {
            freeSegment((void *)&returnAddressAddress);
            freeSegment((void *)&addressLength);
            freeSegment((void *)&addressString);
        }
    }
}

bool checkSuccess(char *addressString, int addressLength, char *input, int addressOverwrite)
{
    if (addressOverwrite < addressLength)
        return false;

    for (int i = 0; i < addressLength; i++)
    {
        if (addressString[i] != input[DEFAULT_CAPACITY * 2 + i])
            return false;
    }
    return true;
}

int digitCount(unsigned long number)
{
    if (number == 0)
        return 1;
    return floor(log10(abs(number))) + 1;
}