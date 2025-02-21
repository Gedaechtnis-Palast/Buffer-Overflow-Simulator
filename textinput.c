#include "textinput.h"
#include <stdio.h>
#include <stdlib.h>

INPUT getInput() {
    INPUT input = {(char *)malloc(10 * sizeof(char)), 0, 10, '\0'};
    while((input.ch = getchar()) != '\n' && input.ch != EOF) {
        if (input.current_size + 1 >= input.capacity) {
            input.capacity *= 2;
            char *temp = realloc(input.buffer, input.capacity * sizeof(char));
            if (temp == NULL) {
                printf("Failed to read input properly.\n");
                free(input.buffer);
                return input;
            }
            input.buffer = temp;
        }
        input.buffer[input.current_size] = input.ch;
        input.buffer[input.current_size+1] = '\0';
        input.current_size++;
    }
    return input;
}