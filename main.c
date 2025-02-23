#include "loopiterator.h"
#include "fileinput.h"
#include <stdbool.h>

#define FILE_PATH_FLAG "-p"
#define AUTO_ATTACK_FLAG "--auto-attack"
#define USE_DEP_FLAG "--use-dep"

int main(int argc, char **argv)
{
    char filename[STR_LEN];
    bool filenameProvided = false;
    bool automatedAttack = false;
    bool depSecurityActive = false;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], FILE_PATH_FLAG) && i + 1 < argc)
        {
            strncpy(filename, argv[i + 1], STR_LEN);
            filenameProvided = true;
        }
        if (!strcmp(argv[i], AUTO_ATTACK_FLAG))
        {
            automatedAttack = true;
        }
        if (!strcmp(argv[i], USE_DEP_FLAG))
        {
            depSecurityActive = true;
        }
    }

    if (automatedAttack)
    {
        printf("automated attack\n");
    }
    if (depSecurityActive)
    {
        printf("DEP security is active\n");
    }

    if (!filenameProvided)
    { // Benutzereingabe für den Dateipfad
        printf("Bitte geben Sie den Dateipfad ein: ");
        if (fgets(filename, STR_LEN, stdin) == NULL)
        {
            fprintf(stderr, "Fehler beim Einlesen des Dateipfads\n");
            return EXIT_FAILURE;
        }

        // Entferne das '\n' am Ende des Eingabestrings
        filename[strcspn(filename, "\n")] = '\0';
    }

    // Datei einlesen
    char *content = readFile(filename);
    if (content != NULL)
    {
        printf("\nDateiinhalt:\n%s\n", content);
        free(content); // Speicher freigeben
    }

    return EXIT_SUCCESS;
}
