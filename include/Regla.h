#ifndef REGLA_H
#define REGLA_H
#include <string>


class Regla
{
    private:
        int idRegla;                    // el numero de la regla
        std::string antecedentes;       // los antecedentes de la regla
        std::string consecuente;        // el consecuente de la regla
        double fc;                      // el factor de certeza de la regla

    public:
        Regla() { }
        Regla(int idRegla, std::string antecedente, std::string consecuente, double certeza);
        ~Regla();
        int getidRegla();                 // para obtener el numero de la regla
        std::string getAntecedentes();       // para obtener los antecedentes (en forma de string con todos los antecedentes)
        std::string getConsecuente();        //para obtener los consecunetes
        double getFC();                      // para obtener el factor de certeza de la regla
};

#endif // REGLA_H
