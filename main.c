#include "memoryMapping.h"
#include "loopEntryAttack.h"
#include "fileinput.h"
#include <stdbool.h>

#define HELP_FLAG "-h"
#define FILE_PATH_FLAG "-p"
#define USE_FILE_INPUT "--use-file-input"
#define AUTO_ATTACK_FLAG "--auto-attack"
#define LOOP_ENTRY_ATTACK "--loop-entry-attack"
#define USE_DEP_FLAG "--use-dep"

void printHelp();

int main(int argc, char **argv)
{
    char filename[STR_LEN];
    bool filenameProvided = false;
    bool automatedAttack = false;
    bool depSecurityActive = false;
    bool doLoopEntryAttack = false;
    bool useFileInput = false;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], HELP_FLAG))
        {
            printHelp();
            return EXIT_SUCCESS;
        }
        if (!strcmp(argv[i], FILE_PATH_FLAG) && i + 1 < argc)
        {
            strncpy(filename, argv[i + 1], STR_LEN);
            filenameProvided = true;
            continue;
        }
        if (!strcmp(argv[i], USE_FILE_INPUT))
        {
            useFileInput = true;
            continue;
        }
        if (!strcmp(argv[i], AUTO_ATTACK_FLAG))
        {
            automatedAttack = true;
            continue;
        }
        if (!strcmp(argv[i], USE_DEP_FLAG))
        {
            depSecurityActive = true;
            continue;
        }
        if (strcmp(argv[i], LOOP_ENTRY_ATTACK))
        {
            doLoopEntryAttack = true;
            continue;
        }
    }

    initMemoryMap();

    char *content;
    if (useFileInput)
    {
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
        content = readFile(filename);
    }

    if (loopEntryAttack)
    {
        if (useFileInput)
        {
            FILE *fp = fopen(filename, "rb");
            loopEntryAttack(content, getFileSize(fp));
            free(fp);
        }
        else
            loopEntryAttack(NULL, 0);
    }
    if (automatedAttack)
    {
        printf("automated attack\n");
    }
    if (depSecurityActive)
    {
        printf("DEP security is active\n");
    }

    return EXIT_SUCCESS;
}

void printHelp()
{
    printf("Usage Options:\n");
    printf("\t%-30s\tUse content of a file instead of a manual input\n", USE_FILE_INPUT);
    printf("\t%-30s\tUse when the program should simulate an attack on its own\n", AUTO_ATTACK_FLAG);
    printf("\t%-30s\tChoose attack with the goal to entry a loop with a buffer overflow\n", LOOP_ENTRY_ATTACK);
    printf("\t%-30s\tEnable DEP security\n", USE_DEP_FLAG);
    printf("\n");
    printf("\t%-30s\tDefine relative or absolute path to a file\n", FILE_PATH_FLAG);
    printf("\t%-30s\tDisplay help text\n", HELP_FLAG);
    printf("\n");
}