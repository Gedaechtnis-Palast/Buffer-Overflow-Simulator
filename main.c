#include "loopiterator.h"
#include <stdlib.h>
#define STR_LEN 80

char* readFile(const char* filename) {
    FILE *fp;
    char *buffer = NULL;
    size_t size = 0;

    // Datei öffnen
    fp = fopen(filename, "r");
    if (fp == NULL){
        fprintf(stderr, "Fehler beim öffnen der Datei '%s'\n", filename);
        return NULL; 
    }
    // Dateigröße ermitteln
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    // Speicher für den inhalt der Datei reservieren
    buffer = (char*)malloc((size + 1) + sizeof(char));
    if (buffer == NULL){
        fprintf(stderr, "Speicherzuweisung felgeschlagen\n");
        fclose(fp);
        return NULL;
    }
    // Dateiinhalt lesen
    fread(buffer, sizeof(char), size, fp); // Nullterminierung
    // Datei schließen
    fclose(fp);

    return buffer;
    
}

int main(){
    const char *filename = "test.txt";
    char *content = readFile(filename);

    if (content != NULL){
        printf("Dateiinhalt:\n%s\n", content);
        free(content); // Speicher freigeben
    }
    return EXIT_SUCCESS;
}
