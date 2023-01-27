#include "Regla.h"
#include <string>
#include <cstdlib>
#include <stdio.h>

using namespace std;

Regla::Regla(int id, string ant, string cons, double certeza)
{
    idRegla = id;
    antecedentes = ant;
    consecuente = cons;
    fc = certeza;
}

Regla::~Regla()
{
    //dtor
}

int Regla::getidRegla()
{
    return idRegla;
}

string Regla::getAntecedentes()
{
    return antecedentes;
}

string Regla::getConsecuente()
{
    return consecuente;
}

double Regla::getFC()
{
    return fc;
}
