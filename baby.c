#include <stdio.h>
#include <stdlib.h>
#include "binary.h"

void loadMem(char** memory);
void printMem(char** memory);
void initMem(char** memory, int inc);
void dissassembleMemory(char** memory);
void allocateMem(char** memory);
void deAllocMem(char** memory);
char* getAccumulator(char* accumulator);
char* getOpcode(char** memory, int pc);
char* getOperand(char** memory, int pc);
int decode(char** memory, int pc);

int main(){

    char* memory[MEMORY_SIZE];
    allocateMem(memory);
    loadMem(memory);
    char* accumulator = malloc(MEMORY_SIZE * sizeof(char));
    strcpy(accumulator, "00000000000000000000000000000000");
    int pc = 0;
    unsigned short runTime = 0; //Making sure it doesn't run too long
    unsigned short opcode = 0;
    // char* opcodeStr;
    char* operand;
    int freeflag;
    char* temp = malloc(MEMORY_SIZE * sizeof(char));
    
    //dissassembleMemory(memory);

    // printf("%d", __UINT16_MAX__);

    while(opcode != 7 || runTime == __UINT16_MAX__){
        printMem(memory);
        printf("\n%d\n", pc);
        if(pc>32 || pc<0){
            break;
        }
        opcode = decode(memory, pc);
        operand = getOperand(memory, pc);
        freeflag = 0;
        int line = 0;
        //printf("%d", line );
        if(opcode == 0){ // JMP S, Jump to the instruction in the operand
            pc = binToDecCompliment(operand);
        }else if(opcode == 1){ // JRP S, Jump to Line number + Operand 
            pc = pc + binToDecCompliment(operand);
        }else if(opcode == 2){ // LDN S, Negate the number at the specified memory address and load to the acc
            line = binToDecCompliment(operand);// gets the line 
            if(line > 32 || line < 0){ //tests to see if it's out of bounds
                printf("Issue at operand 2");
                break;
            }

            free(operand); // frees operand to get the operand loaded at the memory address 
            operand = NULL; // Sets operand to Null to ensure no null pointer
            freeflag = 1;
            operand = getOperand(memory, line); // Gets the operand from the line specified 
            
            // printf("%d %d ", (int)strlen(accumulator), (int)strlen(operand));
            strcpy(accumulator, operand);
        }else if(opcode == 3){ // STO S, Store the number in the accumulator to the specified memory address
            
            strcpy(memory[pc], accumulator);
        }else if(opcode == 4){ // SUB S, Subtract the number from the accumulator and store the answer in the accumulator
            line = binToDecCompliment(operand);
            if(line > 32 || line < 0){
                printf("Issue at operand 2");
                break;
            }
            free(operand);
            operand = NULL;
            freeflag = 1;
            operand = getOperand(memory, line);
            // padBinary(operand);
            // printf("\n%d\n", pc);


        }else if(opcode == 6){ // CMP, skip the next instruction if it's a negative number
             if(binToDecCompliment(operand) < 0)
                pc++;
        }

        pc++;
        if(freeflag == 0){
            free(operand);
            operand = NULL;
        }
    }
    
    free(accumulator);
    accumulator = NULL;
    deAllocMem(memory);
    return 0;

}

void loadMem(char** memory) {
    FILE* file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    
    char test[MEMORY_SIZE];
    int inc = 0;
    
    while (inc < MEMORY_SIZE && fgets(test, sizeof(test), file) != NULL) {

        size_t len = strlen(test);
        if (len > 0 && test[len-1] == '\n'){
            test[len-1] = '\0';
            len--;
        }
        if (len == 0){
            continue;
        }
        if (len < 32){
            memset(test + len, '0', 32 - len);
        }

        test[32] = '\n';
        
        strcpy(memory[inc], test);
        inc++;

    }

    initMem(memory, inc);

    fclose(file);
}

//create a function that prints the memory contents
void printMem(char** memory){
    for(int i = 0; i < MEMORY_SIZE; i++){
        printf("%s", memory[i]);
    }
} 

void initMem(char** memory, int inc){
    char* temp /*= (char *)malloc(MEMORY_SIZE * sizeof(char))*/;
    for(int i = inc; i < MEMORY_SIZE; i++){
        temp = memory[i];
        // printf("%d", strlen(memory[i]));
        // if(strlen(temp) > 0){
        strcpy(temp, "00000000000000000000000000000000\n");
        temp[MEMORY_SIZE] = '\0';
        // }
    }
} 

void allocateMem(char** memory){

    for(int i = 0; i < MEMORY_SIZE; i++){
        memory[i] = (char *)malloc(MEMORY_SIZE * sizeof(char));
        //printf("Iteration: %d\n", i);
        if(memory[i] == NULL){
            printf("Memory allocation failure\n");
            return;
        }
    }
}

void deAllocMem(char** memory){

    for(int i = 0; i < MEMORY_SIZE; i++){
        free(memory[i]);
        memory[i] = NULL;
    }

}

char* getOpcode(char** memory, int pc){
    char* result = (char*) malloc(4 * sizeof(char));
    if(result == NULL){
        printf("getOpcode result malloc failed");
        return NULL;
    }

    strncpy(result, memory[pc] + 13, 3);

    result[3] = '\0';

    return result;

}

char* getOperand(char** memory, int pc){

    char* result = (char*) malloc(13 * sizeof(char));
    if(result == NULL){
        printf("getOpcode result malloc failed");
        return NULL;
    }
    
    strncpy(result, memory[pc], 12);

    result[12] = '\0';

    return result;

}

char* getAccumulator(char* accumulator){

    char* result = (char*) malloc(13 * sizeof(char));
    if(result == NULL){
        printf("getOpcode result malloc failed");
        return NULL;
    }
    
    strncpy(result, accumulator, 12);

    result[12] = '\0';

    return result;

}

int decode(char** memory, int pc){
    
    char* opcode = getOpcode(memory, pc);
    int opReturn = 14;

    if(strcmp(opcode, "000") == 0){
        opReturn = 0;
    }else if(strcmp(opcode, "100") == 0){
        opReturn = 1;
    }else if(strcmp(opcode, "010") == 0){
        opReturn = 2;
    }else if(strcmp(opcode, "110") == 0){
        opReturn = 3;
    }else if(strcmp(opcode, "001") == 0 || strcmp(opcode, "101") == 0){
        opReturn = 4;
    }else if(strcmp(opcode, "011") == 0){
        opReturn = 6;
    }else if(strcmp(opcode, "111") == 0){
        opReturn = 7;
    }else{
        printf("Something has went wrong with the decode function on iteration: %d\n", pc);
        opReturn = 8;
    }

    free(opcode);
    opcode = NULL;
    return opReturn;
}   

void dissassembleMemory(char** memory){

    int opcode;
    char* operand;
    int operandDec = 0;
    for(int i = 0; i < MEMORY_SIZE; i++){
        opcode = decode(memory, i);
        operand = getOperand(memory, i);
        operandDec = binToDecCompliment(operand); 

        if(opcode == 0){
            printf("JMP %d\n", operandDec);
        }else if(opcode == 1){
            printf("JRP %d\n", operandDec);
        }else if(opcode == 2){
            printf("LDN %d\n", operandDec);
        }else if(opcode == 3){
            printf("STO %d\n", operandDec);
        }else if(opcode == 4){
            printf("SUB %d\n", operandDec);
        }else if(opcode == 6){
            printf("CMP %d\n", operandDec);
        }else if(opcode == 7){
            printf("STP %d\n", operandDec);
        }

        free(operand);        
    }


}