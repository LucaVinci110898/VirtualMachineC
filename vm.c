/*
 *  Serafin Tommaso 869835
 *  Vinci Luca 868166
 *  Nome gruppo: P1G102
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esegui.h"
#include "stampa.h"

int main(int argc, char **argv){

  char param;

  if(argc < 3){
    printf("Specificare il file di input\nFormato: ./VM [operazione][nomefile]\n");
    return 0;
  }

  if(!strcmp(argv[1], "stampa"))
    param = 's';
  else if(!strcmp(argv[1], "esegui"))
    param = 'e';
  else{
    printf("Operazione non valida\n");
    return 0;
  }

  switch(param){
    case 'e':
      esegui(argv[2]);
      break;
    case 's':
      stampa(argv[2]);
      break;
    default:
      printf("Operazione non valida\n");
      break;
  }

  return 0;
}




