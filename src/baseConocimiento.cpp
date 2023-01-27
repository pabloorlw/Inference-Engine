#include "baseConocimiento.h"
#include "Regla.h"
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <fstream>


using namespace std;

baseConocimiento::baseConocimiento(istream& fic)
{
    fic >> nReglas;
    fic.ignore();
    reglas = new Regla[nReglas];

    for (int i=0; i < nReglas; i++)
    {
        string linea;
        getline(fic, linea);
        string separador_fc = ", FC=";
        string separador_ent =" Entonces ";
        string separador_si = " Si ";
        string regla = linea.substr(0, linea.find(separador_fc));
        string numRegla = regla.substr(0, regla.find(separador_si));    // Se queda con la parte Ri:
        string antecedentes = regla.substr(numRegla.length() + separador_si.length(), regla.find(separador_ent)- (numRegla.length() + separador_si.length()));
        string consecuente = regla.substr(linea.find(separador_ent) + separador_ent.length(), regla.length());
        string fact_cert = linea.substr(linea.find(separador_fc) + separador_fc.length(), linea.length());
        double certeza;
        sscanf(fact_cert.c_str(), "%lf", &certeza);
        reglas[i] = Regla(i+1, antecedentes, consecuente, certeza);
    }

}

//Constructor de copia

baseConocimiento::baseConocimiento(const baseConocimiento& BC)
{
    nReglas = BC.nReglas;
    reglas = new Regla[nReglas];
    for (int i=0; i < nReglas; i++)
        reglas[i] = Regla(BC.reglas[i]);
}


baseConocimiento::~baseConocimiento()
{
    delete [] reglas;
}

Regla* baseConocimiento::getReglas()
{
    return reglas;
}

int baseConocimiento::getNReglas()
{
    return nReglas;
}

void baseConocimiento::muestraBC()
{
    cout << "Base de conocimiento con " << nReglas << " reglas." << endl;
    for (int i=0; i < nReglas; i++)
        cout << "Regla " << i+1 << ". Antecedentes: " << reglas[i].getAntecedentes() << ". Consecuente: " << reglas[i].getConsecuente() << ". FC=" << reglas[i].getFC() << endl;
}
