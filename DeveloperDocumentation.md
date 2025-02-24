# Developer Documentation

<!-- TOC -->
* [Developer Documentation](#developer-documentation)
  * [Disclaimer](#disclaimer)
  * [Technical Details](#technical-details)
    * [Save User Input](#save-user-input)
    * [Working around kernel level security like DEP (Data Execution Protection) and ASLR (Address Space Layout Randomization)](#working-around-kernel-level-security-like-dep-data-execution-protection-and-aslr-address-space-layout-randomization)
    * [Loop Entry Game](#loop-entry-game)
    * [Return Address Game](#return-address-game)
    * [Memory visualization](#memory-visualization)
<!-- TOC -->

## Disclaimer

A lot of this project is **"Spaghettified"** and not supposed to be used for active development in any way.  
The memory visualization needs to be redesigned in order to be useful in development.

## Technical Details

### Save User Input

For the user input a dynamically increasing char array is used to allow any input size for the buffer.  
Each of the simulations chooses differently on how this buffer is interpreted.

### Working around kernel level security like DEP (Data Execution Protection) and ASLR (Address Space Layout Randomization)

Since this project is supposed to be safe, those security mechanisms did only secure our machines from mistakes made
while programming.  
Simulating those security mechanisms is way harder, since they are already applied the program must somehow simulate the
absence of those mechanisms.  
We chose not to execute any code from a buffer or disable ASLR rather turning it on should show a different success
message stating
that injected code will not be executed even if the return address is perfectly adjusted to jump to the injected code.

### Loop Entry Game

The loop entry attack takes an intersection of the chars and uses bitwise operations to generate a somewhat random
number.  
This number is hopefully in the range of the loops condition, causing a success message to be displayed and ending the
program.

### Return Address Game

The return address attack uses the default size given to the dynamic input to calculate how big the buffer should be to
even reach a buffer overflow and finally the return address.
The overflow on the simulated return address place will now be checked against an address in unsigned long format.   
If the buffer matches the chosen address, the user will receive a success message, ending the program.

### Memory visualization

The memory visualization was by far the biggest challenge, since the memory addresses can reach up to gigantic hex
numbers.  
Our biggest hex number was around 10 digits or 1.1 Trillion addresses, this forced us to find a way of reducing the
possible memory addresses to output drastically.  
One optimization we chose was lowering the possible addresses to the range of the used memory we know the program is
using.  
Here the range is defined by the highest and lowest address found in our program, though visualizing memory is
challenging due to its immense size.  
Static memory occupies the highest addresses, the heap grows downward, and the stack grows upward toward the heap,
spanning almost all the addresses available.  
So separating each area and not filling the space between, minimized the addresses to draw drastically.  
To keep all the addresses the program uses ordered we chose to use a linked list, which is automatically sorted by
lowest to highest address.  
This order comes in handy when filling the spaces between since every address is in order, and allocating/freeing memory
can be easily performed with a linked list.  