//
// Created by albert on 22.06.19.
//

#ifndef PROJEKT_CPP_SZACHY_TURNIEJ_H
#define PROJEKT_CPP_SZACHY_TURNIEJ_H

#define PLIK_Z_ZAWODNIKAMI "zawodnicy.json"

#include "Zawodnik.h"
#include "Runda.h"
#include <vector>
#include <string>
#include <random>

class Turniej {
    std::random_device rd;                            //przyda sie w kojarzeniu
    std::string nazwa_turnieju;                       //przy tworzeniu turnieju trzeba podac z klawiatury
    std::vector<Zawodnik> lista_zawodnikow;           //tu beda wszyscy zawodnicy bioracy udzial w turnieju
    int liczba_rund;                                  //Gdy wiecej niz 8 zawodnikow to 6 rund, w przeciwnym wypadku --> podloga z logarytmu o podstawie dwa z liczby zawodnikow

    std::vector<std::vector<std::size_t>> kto_z_kim_gral;     //indeksowana numerami startowymi zawodnikow  (0 nie gral, 1 on sam lub juz grali, 2 zagra teraz)
    std::vector<Runda> rundy;                                 //obiekty sa dodawane w metodzie kojarzenie()

public:
    Turniej();                                        //trzeba z klawiatury podac nazwe turnieju

    void stworz_zawodnikow()const;                    //dodaje zawodnika do pliku ze wszystkimi zawodnikami
    void dodaj_zawodnikow_do_turnieju();              //jesli mam juz zawodnikow w pliku to dodaje do mojego turnieju
    void ustal_liczbe_rund();                         //trzeba wczesniej miec dodanych zawodnikow
    void stworz_liste_startowa();                     //sortuje liste zawodnikow wedlug rankingu! Tworzy plik z lista startowa, nadaje numery startowe zawodnikom
    void aktualizacja_danych_po_turnieju()const;      //nadpisuje pliki zawodnikow z danymi po turnieju (zeby zaktualizowac rankingi zawodnikow)
    void kojarzenie();                                //ustawia w kto_z_kim_gral na 2 tam kto z kim zagra
    void wpisz_wyniki_rundy();                        //do podawania wynikow kazdej rundy osobno
    void wypisz_kojarzenie()const;                    //podaje kto z kim gra, jakim kolorem
    void podglad();                                   //wypisuje info zawodnikow, ujemne rankingi zeruje
    void wyniki_koncowe();                            //na koncu posortuje zawodnikow wedlug punktow i bucholca i zamienie numery startowe na pozycje koncowe
    void klasyfikacja()const;                         //plik z wynikami

    void start();                                     //Po kolei jak ma dzialac turniej

};


#endif //PROJEKT_CPP_SZACHY_TURNIEJ_H
