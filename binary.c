#include "binary.h"

char* padBinary(char* binary){
    int binaryLength = strlen(binary);
    int paddingNeeded = 13 - binaryLength;
    // Allocate memory for the padded string (+1 for the null terminator)
    char* paddedBinary = malloc(MEMORY_SIZE * sizeof(char));
    if (paddedBinary == NULL)
        return NULL;
    
    // Fill the beginning of paddedBinary with zeros
    for(int i = 0; i < paddingNeeded; i++){
        paddedBinary[i] = '0';
    }
    // Copy the original binary string to the end of the padded zeros
    strcat(binary, paddedBinary);
    free(paddedBinary);
    paddedBinary = NULL;
    return NULL;
}


char* negateString(char* binString){
    if(strcmp("0", binString))
        return NULL;
    int l = strlen(binString);
    char* tempString = malloc(33 * sizeof(char));
    if(tempString == NULL)
        return NULL;
    
    for(int i = 0; i < l; i++){

        if(binString[i] == '1'){
            tempString[i] = '0';
        }else{
            tempString[i] = '1';
        }

    }

    if(tempString[0] == '1'){
        tempString[0] = '0';
    }else if(tempString[0] == '0'){
        tempString[0] = '1';
    }

    strcpy(binString, tempString);
    free(tempString);
    return NULL;
}

char* reverseString(char* binary){

    int binaryLength = strlen(binary);
    char* temp = malloc(33 * sizeof(char));
    if(temp == NULL)
        return NULL;
    for(int i = binaryLength; i>0;i--){
        temp[i] = binary[i];
    }
    strcpy(temp, binary);
    free(temp);
    temp = NULL;
    return NULL;
    
}

int binToDecCompliment(char* binary){

    signed int sum = 0;
    int mult = 1;
    //double comp = -pow(2, (double)strlen(binary)-1); 

    for(int i = 0; i<strlen(binary)-1; i++){

        if(binary[i] == '1'){
            sum+=mult;
        }
        mult *= 2;
    }
    if(binary[strlen(binary)-1] == '0'){
        mult = 0;
    }

    sum = sum + -mult;
    //debug string 
    // printf("Comp: %d\nLength of String: %d\nSum: %d\n", (int)comp, (int)strlen(binary), sum);

    return sum;
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
                sum[i] = '1';
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


char* subStrings(char* string1, char* string2){

    int length = strlen(string1);

    int val1 = binToDec(string1);
    int val2 = binToDec(string2);
    //short int carry = 0;
    //int carryIndex = 0;
    
    char* sum = malloc(MEMORY_SIZE * sizeof(char));
    if(sum == NULL){
        return NULL;
    }
    char* temp1 = malloc(MEMORY_SIZE * sizeof(char));
    if(temp1 == NULL)
        return NULL;
    char* temp2 = malloc(MEMORY_SIZE * sizeof(char));
    if(temp2 == NULL)
        return NULL;

    if(val1 < val2){
        strcpy(temp1, string2);
        strcpy(temp2, string1);
    }else if(val1 > val2){
        strcpy(temp1, string1);
        strcpy(temp2, string2);
    }

    printf("\n%s: %d\n%s: %d\n", temp1, val1, temp2, val2);

    for(int i = 0; i<length; i++){

        if(temp1[i] == '1' && temp2[i] == '1'){
            // if(carry == 1){
            //     sum
            // }
            sum[i] = '0'; 
        }else if(temp1[i] == '1' && temp2[i] == '0'){
            sum[i] = '1';
        }else if(temp1[i] == '0' && temp2[i] == '0'){
            sum[i] = '0';
        }else if(temp1[i] == '0' && temp2[i] == '1'){
            for(int l = i; l < length; l++){
                if(temp1[l] == '0'){
                    temp1[l] = '1';
                }else if(temp1[l] == '1'){
                    temp1[l] = '0';
                    sum[i] = '1';
                    break;
                }
            }
        }else{
            break;
        }

    }
    free(temp1);
    free(temp2);
    temp1 = NULL;
    temp2 = NULL;
    return sum;
}