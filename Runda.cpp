//
// Created by albert on 23.06.19.
//

#include "Runda.h"
#include <iostream>


unsigned int licznik = 1;

Runda::Runda(std::vector<std::vector<std::size_t>> kojarzenie, const std::vector<Zawodnik> &lista_zawodnikow) {

    for(std::size_t h=0;h<kojarzenie.size();h++){
        for(std::size_t g=h;g<kojarzenie.size();g++){
            if ( kojarzenie[g][h] == 2 ) {

                //juz tutaj musze zdecydowac kto gra bialymi a kto czarnymi
                partie.emplace_back(
                        lista_zawodnikow[g].kolor > lista_zawodnikow[h].kolor ? Partia(g, h) : Partia(h, g));  //zmienna kolor jest wieksza jak mial wiecej gier bialymi.     Pierwszy argument bedzie gral CZARNYMI
                                                                                                                           //A GDZIE ZMIENIAM WARTOSCI KOLORU???
                                                                                                                                                            //PRZY WPISYWANIU WYNIKOW ( DOPIERO JAK SIE PARTIA ODBYLA :p)
            }
        }
    }
    numer_rundy = licznik;
    licznik++;
}