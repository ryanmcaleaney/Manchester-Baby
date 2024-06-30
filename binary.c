#include <stdlib.h>
#include <string.h>

char *padBinary(char* binary){
    int binaryLength = strlen(binary);
    int paddingNeeded = 32 - binaryLength;

    // Allocate memory for the padded string (+1 for the null terminator)
    char *paddedBinary = malloc(33 * sizeof(char));
    if (paddedBinary == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    // Fill the beginning of paddedBinary with zeros
    for(int i = 0; i < paddingNeeded; i++){
        paddedBinary[i] = '0';
    }

    // Copy the original binary string to the end of the padded zeros
    strcpy(paddedBinary + paddingNeeded, binary);

    return paddedBinary;
}
