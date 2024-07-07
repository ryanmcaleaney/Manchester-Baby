#include <stdio.h>
#include <stdlib.h>
#include "binary.c"

void loadMem(char** memory);
void printMem(char* memory);

int main(){

    char** memory = malloc((32*33) * sizeof(char));
    char* accumulator = malloc(33 * sizeof(char));
    int pc = 0;


    free(memory);
    free(accumulator);
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
void printMem(char* memory){
    for(int i = 0; i < 32; i++){
        printf("%s\n", memory + (i * 33));
    }