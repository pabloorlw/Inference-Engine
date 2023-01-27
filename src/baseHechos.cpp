#include "baseHechos.h"
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <iterator>
#include <list>

#define NOHECHO -999999
using namespace std;


baseHechos::baseHechos(istream& fic)
{
    fic >> nHechos;
    fic.ignore();
    for (int i=0; i < nHechos; i++)
    {
        string linea;
        getline(fic, linea);
        string separador_fc = ", FC=";
        string h = linea.substr(0, linea.find(separador_fc));
        string fact_cert = linea.substr(linea.find(separador_fc) + separador_fc.length(), linea.length());
        double certeza;
        sscanf(fact_cert.c_str(), "%lf", &certeza);
        Hecho hecho = Hecho(h, certeza);
        hechos.push_back(hecho);

    }
    string aux;
    getline(fic, aux);      // Nos saltamos la linea que pone "objetivo"
    string cadenaObj;
    getline(fic, cadenaObj);
    Hecho obj = Hecho(cadenaObj, 0);          // del objetivo a priori no sabemos su fc, por eso en un prinicipio le ponemos 0
    objetivo = obj;
}


baseHechos::~baseHechos()
{

}

void baseHechos::anadeHecho(Hecho hecho)
{
    hechos.push_back(hecho);
    nHechos++;
}


Hecho baseHechos::getObjetivo()
{
    return objetivo;
}

// Devuelve el hecho de la base de hechos. Si el hecho no esta en la BH devuelve un hecho "vacio" con fc=NOHECHO
Hecho baseHechos::getHecho(Hecho hecho)
{
    list<Hecho>::iterator it;
    for (it = hechos.begin(); it != hechos.end(); ++it)
    {
        if (it->getidHecho() == hecho.getidHecho())
            return *it;
    }
    Hecho noHecho = Hecho("", NOHECHO);
    return noHecho;
}

void baseHechos::muestraBH()
{
    cout << "Base de hechos con " << nHechos << " hechos." << endl;
    list<Hecho>::iterator it;
    it = hechos.begin();
    for (it = hechos.begin(); it != hechos.end(); ++it)
    {
        cout << it->getidHecho() << ", FC=" << it->getFC() << endl;
    }
    cout << "Objetivo: " << objetivo.getidHecho() << endl;


}
