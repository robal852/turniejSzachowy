//
// Created by albert on 22.06.19.
//

#include "Zawodnik.h"
#include "Turniej.h"
#include <iostream>
#include <fstream>
#include "funkcje.h"


Zawodnik::Zawodnik(const std::string &imie_nazwisko) : punkty{0}, buchholz{0}, numer_startowy{0}, kolor{0}, imie_nazwisko{imie_nazwisko}
{

    nlohmann::json zawodnicy = wczytaj_jsona();

    imie = zawodnicy[imie_nazwisko]["Imie"];
    nazwisko = zawodnicy[imie_nazwisko]["Nazwisko"];
    ranking = zawodnicy[imie_nazwisko]["Ranking"];
}


void Zawodnik::wypisz_informacje()
{
    if ( ranking < 0 ){
            ranking = 0;
    }
    std::cout<< numer_startowy << ". " << imie << " " << nazwisko << " " << punkty << " pkt         Ranking: " << ranking <<"         Preferencja koloru: " << kolor << std::endl;
}

void Zawodnik::wypisz_informacje2() const
{
    std::cout<< numer_startowy << ". " << imie << " " << nazwisko << " " << punkty << " pkt, buchholz: " << buchholz << std::endl;
}


