#include "loopiterator.h"

void loopIterator() {
    INPUT input = getInput();
    int *iterations = (int *) &input.buffer + input.current_size/2;

    for(int i = *iterations;  0 <= i && 50 >= i; i++) {
        if(*iterations > 50 || *iterations < 0) {
            printf("How did it end up here? %i", *iterations);
            break;
        }
        printf("Successfully entered the loop!");
    }
}