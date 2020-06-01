//
// Created by albert on 23.06.19.
//

#ifndef PROJEKT_CPP_SZACHY_RUNDA_H
#define PROJEKT_CPP_SZACHY_RUNDA_H

#include <vector>
#include "Partia.h"
#include "Zawodnik.h"

class Runda {
public:
    std::vector<Partia> partie;     //kto z kim gra w danej rundzie
    unsigned int numer_rundy;

    Runda(std::vector<std::vector<std::size_t>> kojarzenie, const std::vector<Zawodnik> &lista_zawodnikow);
};


#endif //PROJEKT_CPP_SZACHY_RUNDA_H
