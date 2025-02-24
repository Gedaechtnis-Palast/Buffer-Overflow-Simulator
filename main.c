#include "memoryMapping.h"
#include "loopEntryAttack.h"
#include "fileinput.h"
#include "returnAddressAttack.h"

#define HELP_FLAG "-h"
#define FILE_PATH_FLAG "-p"
#define USE_FILE_INPUT "--use-file-input"
#define AUTO_ATTACK_FLAG "--auto-attack"
#define LOOP_ENTRY_ATTACK "--loop-entry-attack"
#define RETURN_ADDRESS_ATTACK "--return-address-attack"
#define USE_DEP_FLAG "--use-dep"

void printHelp();
void initProgramMemory();

int main(int argc, char **argv)
{
    char filename[STR_LEN];
    bool filenameProvided = false;
    bool automatedAttack = false;
    bool depSecurityActive = false;
    bool doLoopEntryAttack = false;
    bool doReturnAddressAttack = false;
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
            useFileInput = true;
            continue;
        }
        if (!strcmp(argv[i], USE_FILE_INPUT))
        {
            useFileInput = true;
            continue;
        }
        if (!strcmp(argv[i], AUTO_ATTACK_FLAG))
        {
            printf("Automated attack is not yet implemented\n");
            automatedAttack = true;
            continue;
        }
        if (!strcmp(argv[i], USE_DEP_FLAG))
        {
            printf("DEP security is active\n");
            depSecurityActive = true;
            continue;
        }
        if (!strcmp(argv[i], LOOP_ENTRY_ATTACK))
        {
            if (doReturnAddressAttack)
            {
                printf("You can only do one attack at a time. The return address attack will be performed now.\n");
                continue;
            }
            doLoopEntryAttack = true;
            continue;
        }
        if (!strcmp(argv[i], RETURN_ADDRESS_ATTACK))
        {
            if (doLoopEntryAttack)
            {
                printf("You can only do one attack at a time. The loop entry attack will be performed now.\n");
                continue;
            }
            doReturnAddressAttack = true;
            continue;
        }
    }

    initProgramMemory();

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

    if (doLoopEntryAttack)
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
    if (doReturnAddressAttack)
    {
        returnAddressAttack(NULL, 0, depSecurityActive);
    }
    if (automatedAttack)
    {
        printf("Automated attack is not yet implemented\n");
    }

    return EXIT_SUCCESS;
}

void printHelp()
{
    printf("Usage Options:\n");
    printf("\t%-30s\tUse content of a file instead of a manual input\n", USE_FILE_INPUT);
    printf("\t%-30s\tUse when the program should simulate an attack on its own (coming soon!)\n", AUTO_ATTACK_FLAG);
    printf("\t%-30s\tChoose to attack a loop entry condition with a buffer overflow\n", LOOP_ENTRY_ATTACK);
    printf("\t%-30s\tChoose to attack the return address of a function with a buffer overflow\n", RETURN_ADDRESS_ATTACK);
    printf("\t%-30s\tEnable DEP security (only affects return address attack)\n", USE_DEP_FLAG);
    printf("\n");
    printf("\t%-30s\tDefine relative or absolute path to a file\n", FILE_PATH_FLAG);
    printf("\t%-30s\tDisplay help text\n", HELP_FLAG);
    printf("\n");
}

void initProgramMemory()
{
    initMemoryMap();
    size_t voidPointerSize = sizeof(void *);
    // functions from main.c
    allocStatic(main, main + 89 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(printHelp, printHelp + 12 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(initProgramMemory, initProgramMemory + 29 * voidPointerSize, NULL, voidPointerSize);
    // functions from memoryMapping.h
    allocStatic(createSegment, createSegment + 29 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(createSegmentCollection, createSegmentCollection + 8 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(initMemoryMap, initMemoryMap + 6 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(printMemoryMap, printMemoryMap + 8 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(printSegmentCollection, printSegmentCollection + 41, NULL, voidPointerSize);
    allocStatic(allocStack, allocStack + 3 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(allocHeap, allocHeap + 3 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(allocStatic, allocStatic + 3 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(allocSegment, allocSegment + 89 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(freeSegment, freeSegment + 14 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(freeMemory, freeMemory + 45 * voidPointerSize, NULL, voidPointerSize);
    // functions from loopEntryAttack.h
    allocStatic(loopEntryAttack, loopEntryAttack + 48 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(allocHeapBuffer, allocHeapBuffer + 6 * voidPointerSize, NULL, voidPointerSize);
    // functions from fileinput.h
    allocStatic(readFile, readFile + 40 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(getFileSize, getFileSize + 6 * voidPointerSize, NULL, voidPointerSize);
    // functions from returnAddressAttack.h
    allocStatic(returnAddressAttack, returnAddressAttack + 20 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(checkSuccess, checkSuccess + 11 * voidPointerSize, NULL, voidPointerSize);
    allocStatic(digitCount, digitCount + 5 * voidPointerSize, NULL, voidPointerSize);
}