#ifndef RETURN_ADDRESS_ATTACK_H
#define RETURN_ADDRESS_ATTACK_H

#include "textinput.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void returnAddressAttack(char *fileBuffer, long fileBufferLength);
bool checkSuccess(char *addressString, int returnAddressLength, char *input, int addressOverwrite);
int digitCount(unsigned long number);

#endif
