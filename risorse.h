/*
 *  Serafin Tommaso 869835
 *  Vinci Luca 868166
 *  Nome gruppo: P1G102
 */
struct stack{
    int *stk;
    unsigned int SP;
};
typedef struct stack Stack;

struct registri{
    int *reg;
    int size;
};
typedef struct registri Registro;

struct ip{
    unsigned int IP;
};
typedef struct ip IP;

struct instruction{
    char *mnemonico;
    int len;
    int codice;
    char *P1;
    char *P2;
};
typedef struct instruction Instruction;

Stack init_stack();
Registro init_register();
IP init_IP();

Instruction init_instruction(char *mnemonico, int len, int codice, char *P1, char *P2);
Instruction* init_instruction_set(int *n_ins);
