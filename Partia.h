//
// Created by albert on 23.06.19.
//

#ifndef PROJEKT_CPP_SZACHY_PARTIA_H
#define PROJEKT_CPP_SZACHY_PARTIA_H


class Partia {
public:
    std::size_t biale;                        //numer startowy a zarazem indeks w liscie zawodnikow bialego
    std::size_t czarne;                       //numer startowy zawodnika ktory gral czarnymi
    std::size_t kto_wygral;                   //1 wygraly biale, 0 wygraly czarne , 5 to remis

    Partia(std::size_t a, std::size_t b);             //a to czarne b to biale
};


#endif //PROJEKT_CPP_SZACHY_PARTIA_H
