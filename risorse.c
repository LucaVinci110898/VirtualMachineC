/*
 *  Serafin Tommaso 869835
 *  Vinci Luca 868166
 *  Nome gruppo: P1G102
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "risorse.h"

#define STACK_SIZE 64000/sizeof(int)
#define N_REG 32
#define N_INSTRUCTION 16

Stack init_stack(){
    Stack s;
    s.SP = 0;
    s.stk = (int*)malloc(sizeof(int) * STACK_SIZE);
    if(s.stk == NULL){
        perror("Errore in func init_stack ");
        exit(EXIT_FAILURE);
    }
    return s;
}

Registro init_register(){
    Registro r;
    r.size = N_REG;
    r.reg = (int*)malloc(sizeof(int) * N_REG);
    if(r.reg == NULL){
        perror("Errore in func init_register ");
        exit(EXIT_FAILURE);
    }
    return r;
}

IP init_IP(){
    IP ip;
    ip.IP = 0;
    return ip;
}

Instruction init_instruction(char *mnemonico, int len, int codice, char *P1, char *P2){
    Instruction i;
    i.mnemonico = mnemonico;
    i.len = len;
    i.codice = codice;
    i.P1 = P1;
    i.P2 = P2;
    return i;
}

Instruction* init_instruction_set(int *n_ins){
    Instruction *ins_set;
    ins_set = (Instruction*)malloc(sizeof(struct instruction) * N_INSTRUCTION);
    if(ins_set == NULL){
        perror("Errore in func init_instruction_set");
        exit(EXIT_FAILURE);
    }

    ins_set[0] = init_instruction("HALT",        1, 0,  "",  "");
    ins_set[1] = init_instruction("DISPLAY",     2, 1,  "R", "");
    ins_set[2] = init_instruction("PRINT_STACK", 2, 2,  "",  "");
    ins_set[3] = init_instruction("PUSH",        2, 10, "R", "");
    ins_set[4] = init_instruction("POP",         2, 11, "R", "");
    ins_set[5] = init_instruction("MOV",         3, 12, "R", "");
    ins_set[6] = init_instruction("CALL",        2, 20, "",  "");
    ins_set[7] = init_instruction("RET",         1, 21, "",  "");
    ins_set[8] = init_instruction("JMP",         2, 22, "",  "");
    ins_set[9] = init_instruction("JZ",          2, 23, "",  "");
    ins_set[10] = init_instruction("JPOS",       2, 24, "",  "");
    ins_set[11] = init_instruction("JNEG",       2, 25, "",  "");
    ins_set[12] = init_instruction("ADD",        3, 30, "R", "R");
    ins_set[13] = init_instruction("SUB",        3, 31, "R", "R");
    ins_set[14] = init_instruction("MUL",        3, 32, "R", "R");
    ins_set[15] = init_instruction("DIV",        3, 33, "R", "R");

    *n_ins = N_INSTRUCTION;
    return ins_set;
}

