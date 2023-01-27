#include "Hecho.h"
#include <string>

using namespace std;

Hecho::Hecho(string h, double certeza)
{
    idHecho = h;
    fc = certeza;
}

Hecho::~Hecho()
{
    //dtor
}

string Hecho::getidHecho()
{
    return idHecho;
}

double Hecho::getFC()
{
    return fc;
}
