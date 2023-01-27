#include "baseConocimiento.h"
#include "baseHechos.h"
#include "Regla.h"
#include "Hecho.h"
#include "motorInferencia.cpp"
#include <iostream>
#include <fstream>
#include <iterator>
#include <list>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc >= 3)
    {
        // El primer fichero que le pasamos debe ser el de la Base de Conocimientos
        ifstream fic_BC;
        fic_BC.open(argv[1], ios::in);
        // El segundo fichero que le pasamos debe ser el de la Base de Hechos
        ifstream fic_BH;
        fic_BH.open(argv[2], ios::in);


        if(!fic_BC.is_open())
        {
            cerr << "No se ha podido abrir el fichero de la Base de Conocimiento" << endl;
            return 1;
        }

        if(!fic_BH.is_open())
        {
            cerr << "No se ha podido abrir el fichero de la Base de Hechos" << endl;
            return 1;
        }

        if (fic_BC.is_open() && fic_BH.is_open())
        {
            baseConocimiento BC = baseConocimiento(fic_BC);
            baseHechos BHInicial = baseHechos(fic_BH);

            Hecho objInicial = BHInicial.getObjetivo();

            cout << "Base de Conocimiento empleada: " << argv[1] << endl;
            cout << "Base de Hechos empleada: " << argv[2] << endl << endl;
            cout << endl << objInicial.getidHecho() << ", FC = " << encadenamientoAtras(objInicial, BHInicial, BC) << endl;

            fic_BC.close();
            fic_BH.close();
            return 0;
        }
    }

    else
    {
        cerr << "Numero incorrecto de parametros";
        return 1;
    }

}
