#ifndef BASECONOCIMIENTO_H
#define BASECONOCIMIENTO_H
#include <string>
#include <fstream>
#include "Regla.h"


class baseConocimiento
{
    private:
        int nReglas;                        // numero de reglas de la BC
        Regla* reglas;                      // array con las reglas

    public:
        baseConocimiento(std::istream& fic);                 // El constructor lee el fichero de la BC y almacena los antecedentes, consecuentes y el fc de cada regla
        baseConocimiento(const baseConocimiento& BC);        // Constructor de copia
        ~baseConocimiento();
        Regla* getReglas();                                  // obtiene las reglas de la base de conocimiento
        int getNReglas();
        void muestraBC();
};

#endif // BASECONOCIMIENTO_H
