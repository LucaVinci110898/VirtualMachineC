/*
 *  Serafin Tommaso 869835
 *  Vinci Luca 868166
 *  Nome gruppo: P1G102
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "risorse.h"
#include "leggi.h"

#define STACK_SIZE 64000/sizeof(int)

void esegui(char *filename){

    FILE *fp;

    Stack stack;
    Registro registri;
    IP ip;

    int *codice;
    int dim_codice;

    int i;

    fp = fopen(filename, "r");
    if(fp == NULL){
        perror("Errore apertura file");
        exit(EXIT_FAILURE);
    }
    
    codice = leggi(fp, &dim_codice);

    stack = init_stack();
    registri = init_register();
    ip = init_IP();

    if(dim_codice > 0){
        while(codice[ip.IP] != 0){
            switch(codice[ip.IP]){
                /*DISPLAY*/
                case 1:
                    printf("%d\n", registri.reg[codice[ip.IP+1]]);
                    if((int)ip.IP+2 >= dim_codice){
                        printf("Errore, buffer-overflow\n");
                        exit(EXIT_FAILURE);
                    }
                    ip.IP = ip.IP + 2;
                    break;
                /*PRINT_STACK*/
                case 2:
                    if((int)stack.SP < codice[ip.IP+1]){
                        printf("Errore stampa dello stack\n");
                        exit(EXIT_FAILURE);
                    }
                    for(i = 1; i <= codice[ip.IP+1]; i++){
                        printf("[%5d] %d\n", i, stack.stk[stack.SP-i]);
                    }
                    if((int)ip.IP+2 >= dim_codice){
                        printf("Errore, buffer-overflow\n");
                        exit(EXIT_FAILURE);
                    }
                    ip.IP = ip.IP + 2;
                    break;
                /*PUSH*/
                case 10:
                    if(stack.SP >= STACK_SIZE){
                        printf("Errore, stack overflow, all'indice %d\n", ip.IP);
                        exit(EXIT_FAILURE);
                    }
                    else{
                        if(codice[ip.IP+1] > 31 || codice[ip.IP+1] < 0){
                            printf("Errore, registro non valido\n");
                            exit(EXIT_FAILURE);
                        }
                        stack.stk[stack.SP] = registri.reg[codice[ip.IP+1]];
                        stack.SP = stack.SP + 1;
                        if((int)ip.IP+2 >= dim_codice){
                            printf("Errore, buffer-overflow\n");
                            exit(EXIT_FAILURE);
                        }
                        ip.IP = ip.IP + 2;
                    }
                    break;
                /*POP*/
                case 11:
                    if(stack.SP == 0){
                        printf("Errore, stack underflow, all'indice %d\n", ip.IP);
                        exit(EXIT_FAILURE);
                    }
                    else{
                        stack.SP = stack.SP - 1;
                        if(codice[ip.IP+1] > 31 || codice[ip.IP+1] < 0){
                            printf("Errore, registro non valido\n");
                            exit(EXIT_FAILURE);
                        }
                        registri.reg[codice[ip.IP+1]] = stack.stk[stack.SP];
                        if((int)ip.IP+2 >= dim_codice){
                            printf("Errore, buffer-overflow\n");
                            exit(EXIT_FAILURE);
                        }
                        ip.IP = ip.IP + 2;
                    }
                    break;
                /*MOV*/
                case 12:
                    if(codice[ip.IP+1] > 31 || codice[ip.IP+1] < 0){
                            printf("Errore, registro non valido\n");
                            exit(EXIT_FAILURE);
                        }
                    registri.reg[codice[ip.IP+1]] = codice[ip.IP+2];
                    if((int)ip.IP+3 >= dim_codice){
                        printf("Errore, buffer-overflow\n");
                        exit(EXIT_FAILURE);
                    }
                    ip.IP = ip.IP + 3;
                    break;
                /*CALL*/
                case 20:
                    if(stack.SP >= STACK_SIZE){
                        printf("Errore, stack overflow, all'indice %d\n", ip.IP);
                        exit(EXIT_FAILURE);
                    }
                    else{
                        stack.stk[stack.SP] = ip.IP + 2;
                        stack.SP = stack.SP + 1;
                        if(codice[ip.IP+1] >= dim_codice){
                            printf("Errore, JMP a posizione inaccessibile\n");
                            exit(EXIT_FAILURE);
                        } 
                        ip.IP = codice[ip.IP+1];
                    }
                    break;
                /*RET*/
                case 21:
                    if(stack.SP == 0){
                        printf("Errore, stack underflow, all'indice %d\n", ip.IP);
                        exit(EXIT_FAILURE);
                    }
                    else{
                        stack.SP = stack.SP - 1;
                        ip.IP = stack.stk[stack.SP];
                    }
                    break;
                /*JMP*/
                case 22:
                    if(codice[ip.IP+1] >= dim_codice){
                        printf("Errore, JMP a posizione inaccessibile\n");
                        exit(EXIT_FAILURE);
                    } 
                    ip.IP = codice[ip.IP+1];
                    break;
                /*JZ*/
                case 23:
                    if(stack.SP > 0){
                        if(stack.stk[stack.SP-1] == 0){
                            if(codice[ip.IP+1] >= dim_codice){
                                printf("Errore, JMP a posizione inaccessibile\n");
                                exit(EXIT_FAILURE);
                            }
                            if(codice[ip.IP+1] >= dim_codice){
                                printf("Errore, JMP a posizione inaccessibile\n");
                                exit(EXIT_FAILURE);
                            } 
                            ip.IP = codice[ip.IP+1];
                            stack.SP = stack.SP - 1;
                        }
                        else{
                            stack.SP = stack.SP - 1;
                            if((int)ip.IP+2 >= dim_codice){
                                printf("Errore, buffer-overflow\n");
                                exit(EXIT_FAILURE);
                            }
                            ip.IP = ip.IP + 2;
                        }
                    }
                    else{
                        printf("Errore, stack underflow, all'indice %d\n", ip.IP);
                        exit(EXIT_FAILURE);
                    }
                    break;
                /*JPOS*/
                case 24:
                    if(stack.SP > 0){
                        if(stack.stk[stack.SP-1] > 0){
                            if(codice[ip.IP+1] >= dim_codice){
                                printf("Errore, JMP a posizione inaccessibile\n");
                                exit(EXIT_FAILURE);
                            }
                            if(codice[ip.IP+1] >= dim_codice){
                                printf("Errore, JMP a posizione inaccessibile\n");
                                exit(EXIT_FAILURE);
                            } 
                            ip.IP = codice[ip.IP+1];
                            stack.SP = stack.SP - 1;
                        }
                        else{
                            stack.SP = stack.SP - 1;
                            if((int)ip.IP+2 >= dim_codice){
                                printf("Errore, buffer-overflow\n");
                                exit(EXIT_FAILURE);
                            }
                            ip.IP = ip.IP + 2;
                        }
                    }
                    else{
                        printf("Errore, stack underflow, all'indice %d\n", ip.IP);
                        exit(EXIT_FAILURE);
                    }
                    break;
                /*JNEG*/
                case 25:
                    if(stack.SP > 0){
                        if(stack.stk[stack.SP-1] < 0){
                            if(codice[ip.IP+1] >= dim_codice){
                                printf("Errore, JMP a posizione inaccessibile\n");
                                exit(EXIT_FAILURE);
                            }
                            if(codice[ip.IP+1] >= dim_codice){
                                printf("Errore, JMP a posizione inaccessibile\n");
                                exit(EXIT_FAILURE);
                            } 
                            ip.IP = codice[ip.IP+1];
                            stack.SP = stack.SP - 1;
                        }
                        else{
                            stack.SP = stack.SP - 1;
                            if((int)ip.IP+2 >= dim_codice){
                                printf("Errore, buffer-overflow\n");
                                exit(EXIT_FAILURE);
                            }
                            ip.IP = ip.IP + 2;
                        }
                    }
                    else{
                        printf("Errore, stack underflow, all'indice %d\n", ip.IP);
                        exit(EXIT_FAILURE);
                    }
                    break;
                /*ADD*/
                case 30:
                    if(stack.SP >= STACK_SIZE){
                        printf("Errore, stack overflow, all'indice %d\n", ip.IP);
                        exit(EXIT_FAILURE);
                    }
                    else{
                        /*Controllo validità registri*/
                        if(codice[ip.IP+1] > 31 || codice[ip.IP+1] < 0 || codice[ip.IP+2] > 31 || codice[ip.IP+2] < 0){
                            printf("Errore, registro non valido\n");
                            exit(EXIT_FAILURE);
                        }
                        /*Controllo overflow dovuto all'addizione*/
                        if((registri.reg[codice[ip.IP+1]] > 0) && (registri.reg[codice[ip.IP+2]] > INT_MAX - registri.reg[codice[ip.IP+1]])){
                            printf("Errore overflow\n");
                            exit(EXIT_FAILURE);
                        }
                        /*Controllo underflow dovuto all'addizione*/
                        if((registri.reg[codice[ip.IP+1]] < 0) && (registri.reg[codice[ip.IP+2]] < INT_MIN - registri.reg[codice[ip.IP+1]])){
                            printf("Errore underflow\n");
                            exit(EXIT_FAILURE);
                        }
                        stack.stk[stack.SP] = registri.reg[codice[ip.IP+1]] + registri.reg[codice[ip.IP+2]];
                        stack.SP = stack.SP + 1;
                        if((int)ip.IP+3 >= dim_codice){
                            printf("Errore, buffer-overflow\n");
                            exit(EXIT_FAILURE);
                        }
                        ip.IP = ip.IP + 3;
                    }
                    break;
                /*SUB*/
                case 31:
                    if(stack.SP >= STACK_SIZE){
                        printf("Errore, stack overflow, all'indice %d\n", ip.IP);
                        exit(EXIT_FAILURE);
                    }
                    else{
                        /*Controllo validità registri*/
                        if(codice[ip.IP+1] > 31 || codice[ip.IP+1] < 0 || codice[ip.IP+2] > 31 || codice[ip.IP+2] < 0){
                            printf("Errore, registro non valido\n");
                            exit(EXIT_FAILURE);
                        }
                        /*Controllo overflow dovuto alla sottrazione*/
                        if((registri.reg[codice[ip.IP+2]] < 0) && (registri.reg[codice[ip.IP+1]] > INT_MAX + registri.reg[codice[ip.IP+2]])){
                            printf("Errore overflow\n");
                            exit(EXIT_FAILURE);
                        }
                        /*Controllo underflow dovuto alla sottrazione*/
                        if((registri.reg[codice[ip.IP+2]] > 0) && (registri.reg[codice[ip.IP+1]] < INT_MIN + registri.reg[codice[ip.IP+2]])){
                            printf("Errore underflow\n");
                            exit(EXIT_FAILURE);
                        }
                        stack.stk[stack.SP] = registri.reg[codice[ip.IP+1]] - registri.reg[codice[ip.IP+2]];
                        stack.SP = stack.SP + 1;
                        if((int)ip.IP+3 >= dim_codice){
                            printf("Errore, buffer-overflow\n");
                            exit(EXIT_FAILURE);
                        }
                        ip.IP = ip.IP + 3;
                    }
                    break;
                /*MUL*/
                case 32:
                    if(stack.SP >= STACK_SIZE){
                        printf("Errore, stack overflow, all'indice %d\n", ip.IP);
                        exit(EXIT_FAILURE);
                    }
                    else{
                        /*Controllo validità registri*/
                        if(codice[ip.IP+1] > 31 || codice[ip.IP+1] < 0 || codice[ip.IP+2] > 31 || codice[ip.IP+2] < 0){
                            printf("Errore, registro non valido\n");
                            exit(EXIT_FAILURE);
                        }
                        /*Controllo overflow dovuto alla divisione*/
                        if (registri.reg[codice[ip.IP+1]] > INT_MAX / registri.reg[codice[ip.IP+2]]){
                            printf("Errore overflow\n");
                            exit(EXIT_FAILURE);
                        }
                        /*Controllo underflow dovuto alla divisione*/
                        if (registri.reg[codice[ip.IP+1]] < INT_MIN / registri.reg[codice[ip.IP+2]]){
                            printf("Errore underflow\n");
                            exit(EXIT_FAILURE);
                        }
                        stack.stk[stack.SP] = registri.reg[codice[ip.IP+1]] * registri.reg[codice[ip.IP+2]];
                        stack.SP = stack.SP + 1;
                        if((int)ip.IP+3 >= dim_codice){
                            printf("Errore, buffer-overflow\n");
                            exit(EXIT_FAILURE);
                        }
                        ip.IP = ip.IP + 3;
                    }
                    break;
                /*DIV*/
                case 33:
                    if(stack.SP >= STACK_SIZE){
                        printf("Errore, stack overflow, all'indice %d\n", ip.IP);
                        exit(EXIT_FAILURE);
                    }
                    else{
                        /*Controllo validità registri*/
                        if(codice[ip.IP+1] > 31 || codice[ip.IP+1] < 0 || codice[ip.IP+2] > 31 || codice[ip.IP+2] < 0){
                            printf("Errore, registro non valido\n");
                            exit(EXIT_FAILURE);
                        }
                        if(registri.reg[codice[ip.IP+2]] == 0){
                            printf("Errore, divione per zero, all'indice %d\n", ip.IP);
                            exit(EXIT_FAILURE);
                        }
                        else{
                            stack.stk[stack.SP] = registri.reg[codice[ip.IP+1]] / registri.reg[codice[ip.IP+2]];
                            stack.SP = stack.SP + 1;
                            if((int)ip.IP+3 >= dim_codice){
                                printf("Errore, buffer-overflow\n");
                                exit(EXIT_FAILURE);
                            }
                            ip.IP = ip.IP + 3;
                        }
                    }
                    break;
            
                default:
                    printf("Istruzione non valida\n");
                    exit(EXIT_FAILURE);
                    break;
            }
        }
    }
    
    free(stack.stk);
    free(registri.reg);
    free(codice);

}