typedef struct
{
    int startAddress;
    int endAddress;
    int overflowEndAddress
} SEGMENT;

/**
 * Accepts the start and end address of a variable to map for the memory visualization.
 * Optionally an extra address can be passed to indicate an overflow reaching over the end address.
 * @startAddress the pointer to a variable. (required)
 * @endAddress the pointer to the last allocated cell of an array. (optional)
 * @overflowEndAddress the address indicating the reach of the overflow over the endAddress. (optional)
 */
int allocHeap(void *startAddress, void *endAddress, void *overflowEndAddress);
/**
 * Accepts the start and end address of a variable to map for the memory visualization.
 * Optionally an extra address can be passed to indicate an overflow reaching over the end address.
 * @startAddress the pointer to a variable. (required)
 * @endAddress the pointer to the last allocated cell of an array. (optional)
 * @overflowEndAddress the address indicating the reach of the overflow over the endAddress. (optional)
 */
int allocStack(void *startAddress, void *endAddress, void *overflowEndAddress);
/**
 * Accepts the start and end address of a variable to map for the memory visualization.
 * Optionally an extra address can be passed to indicate an overflow reaching over the end address.
 * @startAddress the pointer to a variable. (required)
 * @endAddress the pointer to the last allocated cell of an array. (optional)
 * @overflowEndAddress the address indicating the reach of the overflow over the endAddress. (optional)
 */
int allocStatic(void *startAddress, void *endAddress, void *overflowEndAddress);