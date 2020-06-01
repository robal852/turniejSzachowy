//
// Created by albert on 22.06.19.
//

#ifndef PROJEKT_CPP_SZACHY_ZAWODNIK_H
#define PROJEKT_CPP_SZACHY_ZAWODNIK_H

#include "json.hpp"
#include "Partia.h"


class Zawodnik {
public:
    std::string imie;
    std::string nazwisko;
    std::string imie_nazwisko;
    int ranking;                  //ranking moze byc ujemny w momencie gdy oblicze ile odjac, a dopiero na pozniej sprawdzam czy mniejszy od zera i zeruje
    std::size_t numer_startowy;

    //w pliku mam jeszcze plec i wiek ale nie uzywam

    int kolor;                              // na poczatku 0, za gre bialymi +1, za gre czarnymi -1 GDY SKOJARZE ZAWODNIKOW TO BEDE POROWNYWAL WZGLEDEM TEJ ZMIENNEJ I PRZYDZIELAL KOLORY TAK BY WARTOSC JAK NAJBLIZEJ ZERA
    double punkty;                          //1 za wygrana, 0 za przegrana, 0.5 za remis
    double buchholz;                        //suma punktow przeciwnikow
    std::vector<int> przeciwnicy;           //zeby policzyc bucholca, sa tu nuery startowe zawodnikow z ktorymi juz gral


    explicit Zawodnik(const std::string &imie_nazwisko); //wczytuje dane z pliku, reszta wyzerowana
    void wypisz_informacje();
    void wypisz_informacje2() const; // tutaj juz z bucholcem
};


#endif //PROJEKT_CPP_SZACHY_ZAWODNIK_H
