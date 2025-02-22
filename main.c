#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 256 // Maximale Länge des Dateipfads

char* readFile(const char* filename) {
    FILE *fp;
    char *buffer = NULL;
    size_t size = 0;

    // Datei öffnen
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Fehler beim Öffnen der Datei '%s'\n", filename);
        return NULL; 
    }

    // Dateigröße ermitteln
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    // Speicher für den Inhalt der Datei reservieren
    buffer = (char*)malloc(size + 1); // +1 für Nullterminierung
    if (buffer == NULL) {
        fprintf(stderr, "Speicherzuweisung fehlgeschlagen\n");
        fclose(fp);
        return NULL;
    }

    // Dateiinhalt lesen
    if (fread(buffer, sizeof(char), size, fp) != size) {
        fprintf(stderr, "Fehler beim Lesen der Datei\n");
        free(buffer);
        fclose(fp);
        return NULL;
    }
    buffer[size] = '\0'; // Nullterminierung hinzufügen

    // Datei schließen
    fclose(fp);
    return buffer;
}

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
