#include <stdio.h>
#include "binary.c"

void loadMem(char* memory);
void printMem(char* memory);

int main(){

    char* memory[32] = malloc((33*32) * sizeof(char));
    char* accumulator = malloc(33 * sizeof(char));
    int pc = 0;




    free(memory);
    free(accumulator);
    return 0;

}

//create a function that loads a text file into memory
void loadMem(char* memory){
    FILE* file = fopen("example.txt", "r");
    if(file == NULL){
        printf("Error opening file\n");
        return;
    }
    char line[33];
    int i = 0;
    while(fgets(line, sizeof(line), file)){
        strcpy(memory + (i * 33), line);
        i++;
    }
    fclose(file);
}

//create a function that prints the memory contents
void printMem(char* memory){
    for(int i = 0; i < 32; i++){
        printf("%s\n", memory + (i * 33));
    }
}


    // printf("%d\n", binToDec("1110"));
    // char* i = addStrings("1111", "1111");
    // printf("%s, \n", i);
    // char* p = padBinary("1011");
    // printf("%s\n", p);
    // char* t = negateString("1010");
    // printf("%s", t);