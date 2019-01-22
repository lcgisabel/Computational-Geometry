// Função para gerenciar:
// - alocação de memória para matrizes;
// - operações básicas em arrays (max, min, mean ...);
// - Erros e Avisos

#pragma once
#ifndef __ArraysLib_h__
#define __ArraysLib_h__

#include <iostream>
#include "util/ExceptionHandler.h"
using namespace std;

template <class arr>void Allocate (arr**  a, int N); //alocar memória de um array

template <class arr>void AllocateAndInit (arr** a, int N, arr value);

template <class arr>void Deallocate (arr** a);//Desaloque a memória

template <class arr>void Alls(arr* a, int N, arr value) ; //Definir toda a matriz para um determinado valor

template <class arr>void Random(arr* a, int N, arr min, arr max) ; //Gera valores aleatórios entre min e max

template <class arr> arr Min(arr* a, int N, int step = 1); //pega o mínimo

template <class arr> arr Max(arr* a, int N, int step = 1); //pega o máximo

template <class arr> void MinMax(arr* a, int N, arr* max, arr* min, int step = 1); //pega o máximo e o minimo

template <class arr>void PrintArray(arr* a, int N, int col, int step = 1); // Imprime todos os valores de um array usando a tabulação de linhas

template <class arr>arr Mean(arr* a, int N, int step = 1); // obtém o valor médio

template <class arr1, class arr2> void Copy(arr1* destination, arr2* source, int N); // copia 2 matrizes


//O CÓDIGO COMEÇA AQUI!!!

template <class arr>
void Allocate(arr** a, int N)
{
    if (*a != NULL)
    {
        Error("Não pode ser alocado");;
    }
    *a = new arr[N];
    if (*a != NULL)
    {
        return;
    }
    else
    {
        Error("Fora da memória");
    }
}

template <class arr>
void AllocateAndInit (arr** a, int N, arr value)
{
    if (*a != NULL)
    {
        Error("Não pode ser alocado");;
    }
    *a = new arr[N];
    if (*a != NULL)
    {
        Alls(*a, N, value);
        return;
    }
    else
    {
        Error("Fora da memória");
    }
}


template <class arr>
void Deallocate (arr** a)
{
    if (*a == NULL)
    {
        return;
    }
    delete [] *a;
    *a = NULL;
    return;
}


template <class arr>
void Alls(arr* a, int N, arr value)
{
    int i;
    for (i = 0; i < N; i++)
    {
        a[i] = value;
    }
    return;

}

template <class arr>
void Random(arr* a, int N, arr min, arr max) //Gera valores aleatórios entre o mínimo e o máximo
{
    int i;
    for (i = 0; i < N; i++)
    {
        a[i] = min + (arr)rand() / RAND_MAX * max;
    }
}

template <class arr>
arr Max(arr* a, int N, int step) //Obtem o valor maximo e mínimo do array
{
    // a variável step é usada para iterar na distância do passo
    arr max = a[0];
    int i;
    int c = step; //pula o primeiro elemento
    for (i = 1; i < N; i++)
    {
        if (a[c] > max)
        {
            max = a[c];
        }
        c = c + step;
    }
    return max;
}

template <class arr>
arr Min(arr* a, int N, int step) //Obtem o valor maximo e mínimo do array
{
    // a variável step é usada para iterar na distância do passo
    arr min = a[0];
    int i;
    int c = step;
    for (i = 1; i < N; i++)
    {
        if (a[c] < min)
        {
            min = a[c];
        }
        c = c + step;
    }
    return min;
}


template <class arr>
void MinMax(arr* a, int N, arr* max, arr* min, int step) // Obtém o valor máximo e mínimo da matriz
{
   // a variável step é usada para iterar na distância do passo
    *min = a[0];
    *max = a[0] ;
    int i;
    int c = step;
    for (i = 1; i < N; i++)
    {
        if (a[c] < *min)
        {
            *min = a[c];
        }
        if (a[c] > *max)
        {
            *max = a[c];
        }
        c = c + step;
    }
}

template <class arr>
void PrintArray(arr* a, int N, int col, int step) // Imprime todos os valores de um array
{
   // a variável step é usada para iterar na distância do passo

    int i, r, c;
    i = 0;
    r = 0;
    c = 0;

    while (1)
    {
        for (c = 0; c < col; c++) 
        {
            cout << " " << a[i] << " ";
            i += step;
            if (i >= N)
            {
                cout << endl;
                return;
            }
        }
        cout << endl;
    }

    return;
}

template <class arr>
arr Mean(arr* a, int N, int step) 
{
// a variável step é usada para iterar na distância do passo

    int i;
    int c = 0;
    arr mean = 0;
    for (i = 0; i < N; i++)
    {
        mean += a[c];
        c = c + step;
    }
    return mean / N;
}
template <class arr1, class arr2>
void Copy(arr1* destination, arr2* source, int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        destination[i] = source[i];
    }
}

#endif
