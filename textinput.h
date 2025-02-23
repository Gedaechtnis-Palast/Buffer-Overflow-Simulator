typedef struct {
    char *buffer;
    int current_size;
    int capacity;
    char ch;
} INPUT;

/**
 * Prompts the user to input some text.
 * The INPUT struct will adapt its size dynamically based on the user input length.
 * @return INPUT struct containing the text
 */
INPUT getInput();

