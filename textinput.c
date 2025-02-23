#include "textinput.h"
#include <stdio.h>
#include <stdlib.h>

INPUT *getInput(int defaultCapacity)
{
    INPUT *input = (INPUT *)malloc(sizeof(INPUT));
    if (input == NULL)
    {
        printf("Failed to read input properly.\n");
        return NULL;
    }
    input->buffer = (char *)malloc(defaultCapacity * sizeof(char));
    if (input->buffer == NULL)
    {
        printf("Failed to read input properly.\n");
        free((void *)input);
        return NULL;
    }
    input->capacity = defaultCapacity;
    input->current_size = 0;
    input->ch = '\0';

    while ((input->ch = getchar()) != '\n' && input->ch != EOF)
    {
        if (input->current_size + 1 >= input->capacity)
        {
            input->capacity *= 2;
            char *temp = (char *)realloc(input->buffer, input->capacity * sizeof(char));
            if (temp == NULL)
            {
                printf("Failed to read input properly.\n");
                free(input->buffer);
                return input;
            }
            input->buffer = temp;
        }
        input->buffer[input->current_size] = input->ch;
        input->buffer[input->current_size + 1] = '\0';
        input->current_size++;
    }
    return input;
}
