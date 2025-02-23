#include "loopiterator.h"
#include "fileinput.h"


int main() {
    char filename[STR_LEN];

    // Benutzereingabe für den Dateipfad
    printf("Bitte geben Sie den Dateipfad ein: ");
    if (fgets(filename, STR_LEN, stdin) == NULL) {
        fprintf(stderr, "Fehler beim Einlesen des Dateipfads\n");
        return EXIT_FAILURE;
    }

    // Entferne das '\n' am Ende des Eingabestrings
    filename[strcspn(filename, "\n")] = '\0';

    // Datei einlesen
    char *content = readFile(filename);
    if (content != NULL) {
        printf("\nDateiinhalt:\n%s\n", content);
        free(content); // Speicher freigeben
    }

    return EXIT_SUCCESS;
}
