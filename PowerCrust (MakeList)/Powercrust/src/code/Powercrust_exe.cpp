#include <stdio.h>
#include <iostream>
#include <fstream>
#include "util/hr_time.h"
#include "util/PowerCrust.h"
#include <stdint.h>
#include "util/shell_io.h"


using namespace std;


double* ptemp; //coordenada de pontos
int N;//número de pontos
vector<double> p;
int main(int argc, char* argv[])
{

    int flag;

    CStopWatch Timer;

    POWERCRUST Surface;//Classe Power Crust 
   
    cout << endl << "PROGRAMA INICIADO!" << endl;


    if (argc > 1) 
    {
        ReadInputs(argc, argv);
    }
    else
    {
        AskForInputs();
    }

    cout << "Importando os pontos...";
    FileManager.Read_Points(&ptemp, &N, inputfile) ;

    p.resize(N * 3);
    Copy(&p[0], &ptemp[0], N * 3);
    Deallocate(&ptemp);


    Timer.startTimer();
    if (N < 4)
    {
        Error("Não há pontos suficientes");
    }

    cout << endl << "Inicializando PowerCrust" << endl;
    Surface.TriangulatePowerCrust(&p, N);
    int nt = Surface.t.size();
	
	 //FileManager.Write_stl(&p[0], atoi(Surface.TriangulatePowerCrust(&p, N)), nt, outputfile);

    Timer.stopTimer();
    cout << "Tempo total: " << Timer.getElapsedTime() / 1000 << " s" << endl;


    cout << endl << "OUTPUT!" << endl;
    cout << "Gerando arquivo de saida...";
    FileManager.Write_stl(&p[0], &Surface.t[0].p1, nt, outputfile);
    cout << "Fim" << endl;

    Surface.FreeMemory();


    cout << endl << "PROGRAMA ENCERRADO!" << endl << endl;
   
    ExitProgram(0);
}
