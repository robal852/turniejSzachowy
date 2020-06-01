//
// Created by albert on 27.06.19.
//

#ifndef PROJEKT_CPP_SZACHY_FUNKCJE_H
#define PROJEKT_CPP_SZACHY_FUNKCJE_H

#include "Zawodnik.h"
#include "Turniej.h"


//stala do wyliczania rankingow (im wieksza tym wieksze beda przyrosty za kazda wygrana)
#define STALA 32


//oblicza przyrosty rankingow po rozegranej partii, dlatego musi przyjac kto_wygral
std::tuple<int, int> oblicz_zdobyty_ranking(int rankingA, int rankingB, int kto_wygral);


//wczytuje zawodnikow z pliku
nlohmann::json wczytaj_jsona();


//zapisuje do pliku z zawodnikami obiekt klasy json
void zapisz_jsona(const nlohmann::json &zawodnicy);


//funkcja do sortowania wedlug rankingu nierosnaco
bool myfunction (const Zawodnik &i, const Zawodnik &j);


//funkcja do sortowania wedlug wynikow turnieju
bool myfunction2 (const Zawodnik &i, const Zawodnik &j);


#endif //PROJEKT_CPP_SZACHY_FUNKCJE_H
