/*
 *  Serafin Tommaso 869835
 *  Vinci Luca 868166
 *  Nome gruppo: P1G102
 */
#include <stdio.h>
#include <stdlib.h>
#include "leggi.h"
#include "risorse.h"

int serch_instruction(int codice, Instruction *ins_set, Instruction *ins, int n_ins){
    int i = 0;
    while(i < n_ins){
        if(ins_set[i].codice == codice){
            *ins = ins_set[i];
            return 1;
        }
        i++;
    }
    return 0;
}

void stampa(char *filename){
    FILE *fp;

    int *codice;
    int dim_codice;
    int index_codice = 0;

    Instruction *instruction_set;
    Instruction instruction;
    int n_ins;

    fp = fopen(filename, "r");
    if(fp == NULL){
        perror("Errore apertura file");
        exit(EXIT_FAILURE);
    }

    codice = leggi(fp, &dim_codice);
    instruction_set = init_instruction_set(&n_ins);
    
    while(index_codice < dim_codice){
        if(serch_instruction(codice[index_codice], instruction_set, &instruction, n_ins)){
            if(instruction.len == 3){
                if(index_codice+3 > dim_codice){
                    printf("Errore, buffer overflow\n");
                    exit(EXIT_FAILURE);
                }
                printf("[%3d] %s %s%d %s%d\n", index_codice, instruction.mnemonico, instruction.P1, codice[index_codice+1], instruction.P2, codice[index_codice+2]);
                index_codice += 3;
            }
            if(instruction.len == 2){
                if(index_codice+2 > dim_codice){
                    printf("Errore, buffer overflow\n");
                    exit(EXIT_FAILURE);
                }
                printf("[%3d] %s %s%d \n", index_codice, instruction.mnemonico, instruction.P1, codice[index_codice+1]);
                index_codice += 2;
            }
            if(instruction.len == 1){
                if(index_codice+1 > dim_codice){
                    printf("Errore, buffer overflow\n");
                    exit(EXIT_FAILURE);
                }
                printf("[%3d] %s \n", index_codice, instruction.mnemonico);
                index_codice += 1;
            }
        }
        else{
            printf("Possibile errore di scrittura nel file all'indice : %d\n\n", index_codice);
            return;
        }
        
    }
    printf("\n");
    free(instruction_set);
    free(codice);
}
