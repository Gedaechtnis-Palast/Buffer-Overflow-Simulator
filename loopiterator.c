#include "loopiterator.h"
void print_binary(unsigned char byte);

void loopIterator() {
    INPUT input = getInput();
    char *iterations = (char *) (input.buffer + (int)(input.current_size/2));

    for(int i = *iterations;  33 <= i && 90 >= i; i++) {
        if(*iterations > 50 || *iterations < 0) {
            printf("How did it end up here? %i", *iterations);
            break;
        }
        printf("Successfully entered the loop!\n");
    }
}