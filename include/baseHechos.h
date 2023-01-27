#ifndef BASEHECHOS_H
#define BASEHECHOS_H
#include "Hecho.h"
#include <string>
#include <fstream>
#include <iterator>
#include <list>

class baseHechos
{
    private:
        int nHechos;                              // numero de hechos de la BH
        std::list<Hecho> hechos;                  // hechos de la BH
        Hecho objetivo;                           // objetivo del problema

    public:
        baseHechos(std::istream& fic);                            // El constructor lee el fichero de la BH y almacena los hechos, el objetivo y el fc de cada hecho
        ~baseHechos();
        void anadeHecho(Hecho hecho);                             // para añadir un hecho a la BH
        Hecho getObjetivo();                                      // obtiene el objetivo actual
        Hecho getHecho(Hecho hecho);                              // comprueba si en la BH  se encuentra el hecho pasado como parametro. Devuelve el hecho si esta en la bh o un hecho vacio si no lo esta
        void muestraBH();
};

#endif // BASEHECHOS_H
