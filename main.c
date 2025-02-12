#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *buffer;
    int current_size;
    int capacity;
    char ch;
} INPUT;

void offByOne();
INPUT getInput();

int main(){
    offByOne();

    return 0;
}

void offByOne() {
    INPUT input = getInput();
    printf("%s\n", input.buffer);
    int *iterations = (int *) &input.buffer + input.capacity/2;

    for(int i = 50; i > *iterations; i--) {
        if(*iterations > 100 || *iterations < 0) {
            printf("%i", *iterations);
            break;
        }
        printf("still running %i times\n", 50 - *iterations);
    }
}

INPUT getInput() {
    INPUT input = {(char *)malloc(2 * sizeof(char)), 0, 2, '0'};
    while((input.ch = getchar()) != '\n' && input.ch != EOF) {
        if (input.current_size + 1 >= input.capacity) {
            input.capacity *= 2;
            char *temp = realloc(input.buffer, input.capacity * sizeof(char));
            if (temp == NULL) {
                printf("Memory reallocation failed.\n");
                free(input.buffer);
                return input;
            }
            input.buffer = temp;
        }
        input.buffer[input.current_size] = input.ch;
        input.current_size++;
    }
    printf("%i %i\n", input.capacity, input.current_size);
    return input;
}
