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

int binToDec(char* binary){

    int sum = 0;
    int mult = 1;
    // Loops through binary string
    for(int i = 0; i<strlen(binary); i++){
        // Add the multiplier to the sum if it equals 1
        if(binary[i] == '1'){
            sum += mult;
        }
        // Increments the mutliplier in as per binary arithmetic
        mult *= 2;
    }

    return sum;
}

char *addStrings(char* string1, char* string2){

    char* sum = malloc(sizeof(char) * 33);
    char carry = '0';

    for(int i = 0; i < 13; i++){

        if(string1[i] == '1' && string2[i] == '1'){
            if(carry == '0'){
                sum[i] = '0';
                carry = '1';
            }else{
                sum[i] = '1';
            }
        }else if(string1[i] == '1' && string2[i] == '0' || string1[i] == '0' && string2[i] == '1'){
            if(carry == '1'){
            sum[i] = '0';
            }else{
                sum[i] == '1';
            }
        }else if(string1[i] == '0' && string2[i] == '0'){
            if(carry == '1'){
                sum[i] = '1';
                carry = '0';
            }else{
                sum[i] = '0';
            }
        }else{
            if(carry == '1'){
                sum[i] = '1';
                carry = '0';
            }else{
                //sum[i] = '0';
            }
        }

    }
    return sum;
}

char* negateString(char* binString){
    int l = strlen(binString);
    char* tempString = malloc(33 * sizeof(char));
    for(int i = 0; i < l; i++){

        if(binString[i] == '1'){
            tempString[i] = '0';
        }else{
            tempString[i] = '1';
        }

    }
    return tempString;
}

char* subStrings(char* string1, char* string2){

    

}