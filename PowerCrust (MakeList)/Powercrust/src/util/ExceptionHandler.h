#ifndef _ExceptionHandler_h
#define _ExceptionHandler_h

#include <stdio.h>
#include <stdlib.h>

bool PAUSE_BEFORE_EXIT = true; 

void Error(const char* error, int flag); //mensagem de erro e encerramento do programa
void Warning(const char* warn);//mensagem warning
void ExitProgram(int exitflag = 0); //encerra programa

void ExitProgram(int exitflag)
{
#ifdef WIN32
    if (PAUSE_BEFORE_EXIT)
    {
        system("pause");
    }

#else#linux "PAUSE"function
    if (PAUSE_BEFORE_EXIT)
    {
        printf("Pressione 'Enter' para encerrar o programa");
        while (getchar() != '\n');
    }

#endif
    exit(exitflag);
}

//Funções
void Error(const char* error, int flag = 1) 
{
    printf("ERRO:");
    printf(error);
    printf("\n");
    ExitProgram(flag);
}
void Warning(const char* warn)
{
    printf("WARNING:");
    printf(warn);
    printf("\n");
}

#endif
