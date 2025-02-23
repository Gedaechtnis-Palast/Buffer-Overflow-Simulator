#include "textinput.h"
#include <stdio.h>

#define DEFAULT_CAPACITY 20

/**
 * Call this method to let the user attempt a buffer overflow attack.
 * The goal is to enter a loop displaying a message a few times, indicating success.
 */
void loopEntryAttack();
