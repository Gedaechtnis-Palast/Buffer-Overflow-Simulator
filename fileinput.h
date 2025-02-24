#ifndef FILE_INPUT_H
#define FILE_INPUT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define STR_LEN 256 // Maximale Länge des Dateipfads

char *readFile(const char *filename);
long getFileSize(FILE *fp);

#endif
