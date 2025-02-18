#include <stdio.h>
#include <stdlib.h>
#define STR_LEN 80

int main(){
    // double array[10];
    // printf("%p", array);
    FILE *fp;
    char *filename = "test.txt";
    // Datei oeffnen und eine Zeile anhaengen
    fp = fopen (filename, "a");
    if (fp == NULL)
    {
        // Fehlerbehandlung
        fprintf (stderr, "Fehler beim Oeffnen der Datei '%s'\n",
        filename);
        return EXIT_FAILURE;
    }
    fprintf(fp, "\nNoch eine Zeile anhaengen ...");
    // Datei schliessen
    fclose(fp);
    if ((fp = fopen (filename, "r")) == NULL)
    {
    // Fehlerbehandlung
        fprintf(stderr, "Fehler beim Öffnen der Datei '%s'\n",
        filename);      
        return EXIT_FAILURE;
    }
    char str[STR_LEN];
    while(fscanf(fp, "%s", str) != EOF) 
        printf ("%s", str);
    // Datei schliessen
    fclose (fp);
    return EXIT_SUCCESS;
}
