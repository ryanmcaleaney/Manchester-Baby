#include <stdio.h>
#include <stdlib.h>
#include "binary.h"

void loadMem(char** memory);
void printMem(char** memory);
void allocateMem(char** memory);
void deAllocMem(char** memory);
char* getOpcode(char** memory, int pc);

int main(){

    char* memory[MEMORY_SIZE];
    allocateMem(memory);
    char* accumulator = malloc(32 * sizeof(char));
    int pc = 0;
    loadMem(memory);
    
    char* buffer;
    char* temp = malloc(5 * 8);
    char* opcode = getOpcode(memory, 0);
    
    printf("%s", opcode);

    free(accumulator);
    accumulator = NULL;
    deAllocMem(memory);
    return 0;

}

//create a function that loads a text file into memory
void loadMem(char** memory){
    FILE* file = fopen("example.txt", "r");
    if(file == NULL){
        printf("Error opening file\n");
        return;
    }
    char line[33];
    int i = 0;
    while(fgets(line, sizeof(line), file)){
        strcpy(memory[i], line);
        i++;
    }
    fclose(file);
}

//create a function that prints the memory contents
void printMem(char** memory){
    for(int i = 0; i < 32; i++){
        printf("%s", memory[i]);
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
        // printf("Iteration: %d\n", i);
    }

}

char* getOpcode(char** memory, int pc){
    char* result = (char*) malloc(4 * sizeof(char));
    if(result == NULL)
        printf("getOpcode result malloc failed");
        return NULL;

    result[0] = '\0';    
    char* temp;
    temp = memory[pc];
    int inc = 0;

    for(int i = 13; i < 16; i++){
        int len = strlen(result);
        result[len] = temp[i];
        result[len + 1] = '\0';
    }

    return result;

}