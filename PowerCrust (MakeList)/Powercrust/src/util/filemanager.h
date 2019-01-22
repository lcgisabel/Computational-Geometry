#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <util/ArraysLib.h>
#include "util/Triangle.h"
#include "util/Coord3D.h"
#include "util/TrianglesFunctions.h"
#include <stdint.h>
#include <string.h>
#include <vector>

//MACROS
#define ERROR_OPENING\
    cout<<"Abrindo: "<<name<<endl;\
    Error("Não é possível abrir o arquivo");

//Erro ao ler o arquivo
#define ERROR_READING\
    cout<<"Lendo: "<<name<<endl;\
    Error("Erro na leitura do arquivo");

//Erro ao localizar arquivo
#define ERROR_FINDING\
    cout<<"Arquivo: "<<name<<endl;\
    Error("Erro ao localizar o arquivo");

class FILE_MANAGER
{
    public:
        //Lendo arquivo de entrada
        void Read_Points(double** p, int* N, char* name);
        void Read_dat(double** p, int* N, char* name);
        void Read_cgo(double** p, int* N, char* name);

        void Read_Extension(char* filename, char* ext);
        //Gerando arquivo 
        template<class T1>void Write_dat(T1* t, int nt, char* path); // Grava um arquivo .dat listando índices de triangulos (as normais não são impressas!)
        template<class T1>void Write_m(T1* p, int N, int* t, int n, char* path) ;
        void Write_stl(double* inputp, int* t, int nt, char* path);

    private:
        void ChangeChar(char* line, char oldchar, char newchar );

};

template<class T1>
void FILE_MANAGER::Write_dat(T1* t, int nt, char* path) // Grava um arquivo .dat listando índices de triangulos (as normais não são impressas!)
{

    int i, c;
    size_t nwritten;
    FILE* pFile;
    pFile = fopen(path, "wb"); //wb per dire che il file è binario

    //TRIANGLES
    //first line (the number of triangles)
    nwritten = fwrite(&nt, sizeof(int), 1, pFile);

    //Aggiungere l'errocheck se nt=0;

    //TRIANGLES
    //Copy in the temporary array
    c = 0; //intialize
    for (i = 0; i < nt; i++)
    {

        nwritten = fwrite(t, sizeof(int), 3, pFile);
    }

    fclose(pFile);

}
template<class T1>
void FILE_MANAGER::Write_m(T1* p, int N, int* t, int nt, char* path)
{

    int i, c;

    ofstream myfile;
    myfile.open(path);


    //POINTS
    myfile << "p=[\n";
    c = 0;
    for (i = 0; i < N; i++)
    {
        myfile << p[c] << " " << p[c + 1] << " " << p[c + 2] << endl;
        c = c + 3;
    }
    myfile << "];\n";

    //TRIANGLES
    myfile << "t=[\n";
    c = 0;
    for (i = 0; i < nt; i++)
    {
        if (t[c] >= 0)
        {
            myfile << t[c] << " " << t[c + 1] << " " << t[c + 2] << endl;
        }
        c = c + 3;
    }
    myfile << "];\n";

    myfile << "t=t+1;" << endl;
    myfile << "trisurf(t,p(:,1),p(:,2),p(:,3));";

    myfile.close();





}

void FILE_MANAGER::Write_stl(double* inputp, int* inputt, int nt, char* path)

{
    int i, c, id;
    size_t nwritten;
    FILE* pFile;
    Coord3D tnorm;
    Coord3D* p;
    p = (Coord3D*)inputp;
    Triangle* t;
    t = (Triangle*)inputt;


    pFile = fopen(path, "wb"); //wb per dire che il file è binario

    char header[80] = {"GLProduct"};



    float data[12];
    uint16_t option = 0; //set to zero for compatibility of STL files



    //TRIANGLES
    //first line (the header)
    nwritten = fwrite(&header[0], sizeof(char), 80, pFile);

    //the number of triangles
    nwritten = fwrite(&nt, sizeof(int), 1, pFile);





    //TRIANGLES
    //Copy in the temporary array
    c = 0; //intialize
    for (i = 0; i < nt; i++)
    {

        if (t[i].p1 < 0)
        {
            continue;   //Triagnle deleted skip
        }

        TNorm(&p[t[i].p1], &p[t[i].p2], &p[t[i].p3], &tnorm);
        //normal
        data[0] = tnorm.x;
        data[1] = tnorm.y;
        data[2] = tnorm.z;

        //First point
        id = t[i].p1;
        data[3] = p[id].x;
        data[4] = p[id].y;
        data[5] = p[id].z;

        //Second point
        id = t[i].p2;
        data[6] = p[id].x;
        data[7] = p[id].y;
        data[8] = p[id].z;


        //Third point
        id = t[i].p3;
        data[9] = p[id].x;
        data[10] = p[id].y;
        data[11] = p[id].z;

        //Write data

        nwritten = fwrite(&data[0], sizeof(float), 12, pFile);
        nwritten = fwrite(&option, sizeof(uint16_t), 1, pFile);
    }

    fclose(pFile);

}


void FILE_MANAGER::Read_dat(double** p, int* N, char* name)
{
    //Legge un file .dat ealloca la memoria in p. Ritorna il numero di punti in N


    //Dichiarazioni
    FILE* pFile ;
    size_t nread;

    //Inizio
    pFile = fopen(name, "rb");//Open the input binary file

    if (pFile  == NULL)
    {
        ERROR_OPENING
    }

    //leggi la prima riga (numero di punti)
    nread = fread( N, sizeof(int), 1, pFile ); //lettura numero di punti punti
    if (nread != 1)
    {
        ERROR_READING
    }
    Allocate(p, *N * 3); //allocate memory
    nread = fread( *p, sizeof(double), *N * 3, pFile ); //lettura punti
    if (nread != *N * 3)
    {
        ERROR_READING
    }

    fclose(pFile );
}

void FILE_MANAGER::ChangeChar(char* line, char oldchar, char newchar )
{
    //Reads a char array and change the oldchar into the newchar

    int i = 0;
    while (line[i] != 0)
    {
        if (line[i] == oldchar)
        {
            line[i] = newchar;
        }
        i++;
    }
}
void FILE_MANAGER::Read_cgo(double** p, int* N, char* name)
{
    //legge un file cgo e copia dentro l'appena allcoato array p


    //Dichiarazioni
    const int nline = 100; //numbers of char to read for each line
    char line[nline] ;//read line
    FILE* pFile ;
    //size_t nread;
    double* ptr;

    //Inizio
    pFile = fopen(name, "r");//Open the input binary file

    if (pFile  == NULL)
    {
        ERROR_OPENING;
    }

    //first line numbers of points
    if (fgets(line, nline, pFile) != NULL )
    {
        sscanf(line, "%d", N);
    }
    else
    {
        ERROR_READING
    }

    if (*N < 1)
    {
        ERROR_READING
    }

    Allocate(p, *N * 3); //allocate memory
    ptr = *p; //extracting pointer to doubles array
    int i = 0;
    while (fgets(line, nline, pFile) != NULL)
    {
        ChangeChar(line, ',', '.'); //change comma to point
        sscanf(line, "%lf %lf %lf", &ptr[i], &ptr[i + 1], &ptr[i + 2]); //read floating points numbers
        i = i + 3;
        if (i >= *N * 3)
        {
            break;    //non superare il numero di punti
        }
    }

    if (i != *N * 3)
    {
        ERROR_READING
    }
    fclose(pFile );
}

void FILE_MANAGER::Read_Extension(char* name, char* ext)
{
    //reads the file extension and writes it into char ext[4]

    int i = 0;
    int c = 0; //extensions char readen
    bool dotfound = false;
    while (name[i] != 0 && c < 3)
    {
        if (dotfound)
        {
            ext[c] = name[i];  //copy ext char
            c++;
        }
        if (name[i] == '.')
        {
            dotfound = true;
        }
        i++;
    }
    if (c < 3 || !dotfound)
    {
        ERROR_READING
    }
    ext[3] = 0; //add null pointer at the end
}

void FILE_MANAGER::Read_Points(double** p, int* N, char* name)
{
    //Reads point from a point cloud file format

    char ext[4];//file extension


    Read_Extension(name, &ext[0]);


    if (strcmp ("dat", ext) == 0) //read dat file
    {
        Read_dat(p, N, name);
    }
    else if (strcmp ("cgo", &ext[0]) == 0) //read cgo file
    {
        Read_cgo(p, N, name);
    }
    else
    {
        cout << " File: " << name << endl;
        Error("unknow extension");
    }


}

#endif
