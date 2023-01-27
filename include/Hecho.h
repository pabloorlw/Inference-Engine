#ifndef HECHO_H
#define HECHO_H
#include <string>


class Hecho
{
    private:
        std::string idHecho;
        double fc;

    public:
        Hecho() {}
        Hecho(std::string h, double certeza);
        ~Hecho();
        std::string getidHecho();
        double getFC();

};

#endif // HECHO_H
