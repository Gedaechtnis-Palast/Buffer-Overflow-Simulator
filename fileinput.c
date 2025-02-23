#include "fileinput.h"

char* readFile(const char* filename) {
    FILE *fp;
    char *buffer = NULL;
    size_t size = 0;

    // Datei öffnen
    fp = fopen(filename, "rb");
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