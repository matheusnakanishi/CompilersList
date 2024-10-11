#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// ./l6e1 < InOut_06/entrada_01.txt > saida.txt
// diff InOut_06/saida_01.txt saida.txt

#define N_ALF 20
#define N_FINAL 12

int getIndex(char *alfabeto, char simbolo) {
    for(int i = 0; i < N_ALF; i++) {
        if(alfabeto[i] == simbolo) 
            return i;       
    }
    return -1;  // se o simbolo nao pertencer ao alfabeto
}

bool ehFinal(int *estadosF, int estadoAtual) {
    for(int i = 0; i < N_FINAL; i++) {
        if(estadosF[i] == estadoAtual) 
            return true;
    }
    return false;
}

void printToken(bool *mudouEstado, char *impressao) {
    if(*mudouEstado) 
        printf("\n");  
    printf("%s", impressao);
    *mudouEstado = true;
}

void printNumber(char *output, int tam) {
    printf(" ");
    for(int i = 0; i < tam; i++) 
        printf("%c", output[i]);  
}

void clearOutput(char *output, int tam, int *outputIndex) {
    output[0] = '\0';  
    *outputIndex = 0;
}

void updateVar(int *index, int novoIndex, int *backupIndex, int *final, int *estadoAtual) {
    *estadoAtual = 1;
    *final = 0;
    *index = novoIndex;
    *backupIndex = *index;
}

int main() {
    char alfabeto[N_ALF] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                            'h', 'e', 'r', 's', 'i', 'c', 'a', 't', '+', '-'};
    int edges[][N_ALF] = {
        {19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 2, 0, 0, 4, 0, 11, 0, 0, 17, 18},  // state 1
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 7, 0, 0, 0, 0, 0},               // state 2
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0},               // state 3
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // state 4
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0},               // state 5
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // state 6
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0},               // state 7
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // state 8
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0},              // state 9
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // state 10
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0},              // state 11
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 0, 0, 0, 13, 0, 0},             // state 12
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0},              // state 13
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0},              // state 14
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // state 15
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // state 16
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // state 17
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // state 18
        {19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0},    // state 19
        {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 0, 0, 0, 0, 0, 0, 0, 0, 21, 21},   // state 20
        {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     // state 21
        {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     // state 22
    };

    int estadosF[] = {3, 6, 8, 10, 13, 14, 15, 16, 17, 18, 19, 22};
    char *tokens[] = {"nda", "nda", "ELE", "nda", "nda", "ELA", "nda", "DELE", "nda", "DELA",
                      "nda", "nda", "GATO", "CARRO", "GATOS", "CARROS", "MAIS", "MENOS", "INTEIRO", "nda", "nda", "REAL"};

    bool mudouEstado = false;
    char input[4096];
    char output[4096];
    int outputIndex = 0;
    int printIndex = 0;

    while(fgets(input, 4096, stdin) != NULL) {
        int estadoAtual = 1;       
        int index = 0;              
        int backupIndex = 0;       
        int final = 0;              

        while(input[index] != '\0') {
            int charIndex = getIndex(alfabeto, input[index]);  

            if(charIndex == -1) {
                if(final == 0) {
                    if(index == 0) {
                        if(input[index] != 10 && input[index] != 32) 
                            printToken(&mudouEstado, "ERRO");                        
                        updateVar(&index, (index + 1), &backupIndex, &final, &estadoAtual);
                        continue;
                    }
                    updateVar(&index, (backupIndex + 1), &backupIndex, &final, &estadoAtual);
                    if(input[index - 1] == 10 || input[index - 1] == 32) 
                        continue;
                    printToken(&mudouEstado, "ERRO");
                    clearOutput(output, strlen(output), &outputIndex);
                    continue;
                }

                if(final != estadoAtual) {  
                    index = backupIndex;
                    backupIndex = index;
                }

                if(final != 0) {  
                    printf("%s", tokens[final - 1]);
                    if(final == 22 || final == 19)  
                        printNumber(output, printIndex);                   
                    mudouEstado = true;
                }

                clearOutput(output, strlen(output), &outputIndex);
                updateVar(&index, (index + 1), &backupIndex, &final, &estadoAtual);
                if(input[index - 1] == 10 || input[index - 1] == 32) 
                    continue;  
                printToken(&mudouEstado, "ERRO");
                continue;
            }

            int proxEstado = edges[estadoAtual - 1][charIndex];

            if(proxEstado == 0) {
                if(final == 0) {  
                    printToken(&mudouEstado, "ERRO");
                    clearOutput(output, strlen(output), &outputIndex);
                    updateVar(&index, (backupIndex + 1), &backupIndex, &final, &estadoAtual);
                    continue;
                }
                if(final != 0) {  
                    printf("%s", tokens[final - 1]);
                    backupIndex = index;
                }

                if(estadoAtual == final) {  
                    if(final == 22 || final == 19) 
                        printNumber(output, printIndex);                
                } else {  
                    index = backupIndex - 1;
                    backupIndex = index;
                }
                clearOutput(output, strlen(output), &outputIndex);
                mudouEstado = true;
                final = 0;
                estadoAtual = 1;
                continue;
            }

            estadoAtual = proxEstado;                           

            if(ehFinal(estadosF, estadoAtual)) {
                final = estadoAtual;
                printIndex = outputIndex + 1;
            }

            if(input[index] != 10 && input[index] != 32) {  
                if(mudouEstado) {
                    printf("\n");
                    mudouEstado = false;
                }
                output[outputIndex] = input[index];
                outputIndex++;
            }
            index++;
            if(ehFinal(estadosF, estadoAtual)) 
                backupIndex = index;
        }

        if(final == estadoAtual) {
            backupIndex = index;
            printf("%s", tokens[final - 1]);
            if(final == 22 || final == 19) 
                printNumber(output, printIndex);          
            mudouEstado = true;

        } else {  
            if(input[backupIndex] == 10 || input[backupIndex] == 32 || input[backupIndex] == 0) 
                continue;
            printToken(&mudouEstado, "ERRO");
            updateVar(&index, (backupIndex + 1), &backupIndex, &final, &estadoAtual);
        }
        clearOutput(output, strlen(output), &outputIndex);
    }

    return 0;
}