#include "loopiterator.h"
#include "fileinput.h"

#define FILE_PATH_FLAG "-p"

int main(int argc, char **argv)
{
    char filename[STR_LEN];

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], FILE_PATH_FLAG) && i + 1 < argc)
        {
            strncpy(filename, argv[i + 1], STR_LEN);
            printf("filename: %s\n", filename);
        }
        printf("%s\n", argv[i]);
    }
    return EXIT_SUCCESS;

    // Benutzereingabe für den Dateipfad
    printf("Bitte geben Sie den Dateipfad ein: ");
    if (fgets(filename, STR_LEN, stdin) == NULL)
    {
        fprintf(stderr, "Fehler beim Einlesen des Dateipfads\n");
        return EXIT_FAILURE;
    }

    // Entferne das '\n' am Ende des Eingabestrings
    filename[strcspn(filename, "\n")] = '\0';

    // Datei einlesen
    char *content = readFile(filename);
    if (content != NULL)
    {
        printf("\nDateiinhalt:\n%s\n", content);
        free(content); // Speicher freigeben
    }

    return EXIT_SUCCESS;
}
