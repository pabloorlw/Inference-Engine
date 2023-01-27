#include "baseConocimiento.h"
#include "baseHechos.h"
#include "Regla.h"
#include "Hecho.h"
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


// Vamos a devolver una lista con las reglas de la BC cuyo consecuente sea la meta pasada por parametro
list<Regla> equipararCons(baseConocimiento BC, Hecho meta)
{
    Regla* reglasBC = BC.getReglas();
    list<Regla> reglas;
    list<Regla>::iterator it = reglas.begin();
    for (int i=0; i < BC.getNReglas(); i++)
    {
        if (meta.getidHecho() == reglasBC[i].getConsecuente())
            reglas.push_back(reglasBC[i]);

        ++it;
    }
    return reglas;
}

// Devuelve una lista con los antecedentes de una regla pasada como parametro. El ultimo elemento de la lista
// va a ser el tipo de relacion que guardan los antecedentes (si es una disyuncion: "o" o una conjuncion: "y")
list<string> extraerAntecedentesyTipo(Regla R)
{
    // Hay que procesar la cadena en la que se guardan los antecedentes que puede ser del tipo: "A", "A o B", "A y B", "A o B o C"...
    list<string> antecedentesTipo;
    string antecedentesR = R.getAntecedentes();

    stringstream ss(antecedentesR);
    string antecedente;
    string tipo = " ";

    while(getline(ss, antecedente, ' '))
    {
        if (antecedente == "o")
            tipo = "o";
        else if (antecedente == "y")
            tipo = "y";
        else
            antecedentesTipo.push_back(antecedente);
    }
    antecedentesTipo.push_back(tipo);
    return antecedentesTipo;
}


// Calcula el FC combinado de los antecedentes de una regla R (Caso 1). El parametro "tipo"
// indica si los antecedentes estan relacionados por una disyuncion o por una conjuncion
double calcularFCAnt(Regla R, list<double> fcNuevasMetas, string tipo)
{
    list<double>::iterator it = fcNuevasMetas.begin();
    if ((fcNuevasMetas.size() > 1) && (tipo != " "))
    {
        if (tipo == "y")
        {
            double min = 1;
            while(it != fcNuevasMetas.end())
            {
                if (*it < min)
                    min = *it;
                ++it;
            }
            cout << "\tCaso 1: " << R.getAntecedentes() << ", FC = " << min << endl;
            return min;
        }
        else
        {
            double max = -1;
            while(it != fcNuevasMetas.end())
            {
                if (*it > max)
                    max = *it;
                ++it;
            }
            cout << "\tCaso 1: " << R.getAntecedentes() << ", FC = " << max << endl;
            return max;
        }
    }
    // Una regla puede tener un solo antecedente, en ese caso la lista que le pasamos
    // por parametro a la funcion solo contiene un elemento (el FC del unico antecedente)
    else
        return *it;
}

// Calcula el FC de una meta por la regla R (Caso 3). El parametro fcAntecedentesR es el FC
// de los antecedentes combinados de la regla R y fcR es el FC de la regla R
double calcularFCMetaR(Hecho meta, double fcAntecedentesR, double fcR)
{
    if (fcAntecedentesR <= 0)
    {
        cout << "\tCaso 3: " << meta.getidHecho() << ", FC = 0" << endl;
        return 0;
    }
    else
    {
        double resul = fcR*fcAntecedentesR;
        cout << "\tCaso 3: " << meta.getidHecho() << ", FC = " << resul << endl;
        return resul;
    }
}

// Calcula el FC de una meta si hay mas de 2 reglas que nos llevan a esa meta (Caso 2)
// Hacemos una funcion recursiva
double calcularFCcombinacion(Hecho meta, list<double> fcMetas)
{
    list<double>::iterator it;
    if (fcMetas.size() == 2)            // Caso base
    {
        it = fcMetas.begin();
        double fc1 = *it;
        double fc2 = *(++it);
        double resul;
        if ((fc1 >= 0) && (fc2 >= 0))
            resul = fc1 + fc2*(1-fc1);
        else if ((fc1 <= 0) && (fc2 <= 0))
            resul = fc1 + fc2*(1+fc1);
        else
            resul = (fc1 + fc2)/(1-min(fabs(fc1), fabs(fc2)));

        cout << "Caso 2: " << meta.getidHecho() << ", FC = " << resul << endl;
        return resul;
    }
    else
    {
        double fc1 = fcMetas.back();
        fcMetas.pop_back();
        double fc2 = calcularFCcombinacion(meta, fcMetas);
        double resul;
        if ((fc1 >= 0) && (fc2 >= 0))
            resul = fc1 + fc2*(1-fc1);
        else if ((fc1 <= 0) && (fc2 <= 0))
            resul=fc1 + fc2*(1+fc1);
        else
            resul =(fc1 + fc2)/(1-min(fabs(fc1), fabs(fc2)));

        cout << "Caso 2: " << meta.getidHecho() << ", FC = " << resul << endl;
        return resul;

    }
}


double encadenamientoAtras(Hecho meta, baseHechos BH, baseConocimiento BC)
{
    double fc = BH.getHecho(meta).getFC();
    if (fc >= -1)
        return fc;

    else
    {
        list<Regla> cjtoReglas;                  // Conjunto de reglas cuyos consecuentes coinciden con la meta
        cjtoReglas = equipararCons(BC, meta);    // buscamos las reglas de la BC cuyos consecuentes sean la meta
        list<double> fcMetas;                    // lista para guardar los FC
        while (!cjtoReglas.empty())
        {
            Regla R = cjtoReglas.front();                       // se elige la primera regla del cjtoReglas
            cjtoReglas.pop_front();                             // se elimina esta regla del cjtoReglas
            double fcR = R.getFC();                             // guardamos el fc de la regla R
            list<string> antecedentesTipo = extraerAntecedentesyTipo(R);
            string tipo = antecedentesTipo.back();              // tipo nos va a determinar si tenemos una conjuncion o disyuncion entre los antecedentes
            antecedentesTipo.pop_back();                        // eliminamos el tipo de la lista ya que no es un antecedente
            list<string> nuevasMetas = antecedentesTipo;
            list<double> fcNuevasMetas;                         // guarda el factor de certeza de cada una de las nuevas metas
            while (!nuevasMetas.empty())
            {
                string nMeta = nuevasMetas.front();                  // se elige la primera meta de nuevasMetas
                nuevasMetas.pop_front();                             // se elimina esta meta de nuevasMetas

                Hecho hechoNMeta = Hecho(nMeta, 0);
                double fc = encadenamientoAtras(hechoNMeta, BH, baseConocimiento(BC));
                fcNuevasMetas.push_back(fc);

            }
            cout << "R" << R.getidRegla() << ":" << endl;
            // Vamos a calcular el FC combinado de los antecedentes de la regla R (Caso 1: puede ser conjuncion o disyuncion)
            double fcAntecedentesR = calcularFCAnt(R, fcNuevasMetas, tipo);

            // Vamos a calcular el FC de la meta por la regla R (Caso 3)
            double fcMetaR = calcularFCMetaR(meta, fcAntecedentesR, fcR);
            fcMetas.push_back(fcMetaR);

        }
        // Finalmente, vamos a calcular el FC de la meta si hay mas de 2 reglas que nos llevan a esa meta (Caso 2)
        double fcMeta;
        if (fcMetas.size() == 1)
            fcMeta = fcMetas.front();
        else
            fcMeta = calcularFCcombinacion(meta, fcMetas);
        return fcMeta;
    }
}

