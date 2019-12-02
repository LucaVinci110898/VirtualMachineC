/*
 *  Serafin Tommaso 869835
 *  Vinci Luca 868166
 *  Nome gruppo: P1G102
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "leggi.h"
#include "risorse.h"

#define NUM_BUFF_SIZE 1000

int* leggi(FILE *fp, int *dim){
    
    char *buffer = NULL;
    size_t buffer_size = 0;
    size_t index_buffer;
    int line_size;

    int *codice = NULL;
    int dim_codice = 0;
    int index_codice = 0;

    char num_buffer[NUM_BUFF_SIZE];
    int index_num_buffer;
    

    while((line_size = getline(&buffer, &buffer_size, fp)) != -1){
        index_num_buffer = 0;
        index_buffer = 0;
        if(dim_codice == 0){
            while(index_buffer < buffer_size && buffer[index_buffer] != '\n' && buffer[index_buffer] != '\r' && buffer[index_buffer] != ';'){
                if(buffer[index_buffer] >= '0' && buffer[index_buffer] <= '9'){
                    num_buffer[index_num_buffer] = buffer[index_buffer];
                    index_num_buffer++;
                }
                index_buffer++;
            }
            if(index_num_buffer > 0){
                num_buffer[index_num_buffer] = '\0';
                dim_codice = atoi(num_buffer);
                codice = (int*)malloc(sizeof(int) * dim_codice);
                if(codice == NULL){
                    perror("Errore in func leggi ");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else{
            if(index_codice < dim_codice){
                while(index_buffer < buffer_size && buffer[index_buffer] != '\n' && buffer[index_buffer] != '\r' && buffer[index_buffer] != ';'){
                    if(buffer[index_buffer] >= '0' && buffer[index_buffer] <= '9'){
                        num_buffer[index_num_buffer] = buffer[index_buffer];
                        index_num_buffer++;
                    }
                    index_buffer++;
                }
                if(index_num_buffer > 0){
                    num_buffer[index_num_buffer] = '\0';
                    codice[index_codice] = atoi(num_buffer);
                    index_codice++;
                }
            }
        }
    }
    
    free(buffer);
    *dim = dim_codice;
    return codice;
}