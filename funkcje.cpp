//
// Created by albert on 27.06.19.
//

#include "funkcje.h"
#include <fstream>
#include <iomanip>


std::tuple<int, int> oblicz_zdobyty_ranking(int rankingA, int rankingB, int kto_wygral){

    std::tuple <int, int> rankingi;
    int ranking_uzyskanyA;
    int ranking_uzyskanyB;

    //z intow na double co by w oblizeniach nie bylo problemu
    double rankingAA = rankingA;
    double rankingBB = rankingB;

    double roznicaA = (rankingAA - rankingBB)/400; //na podstawie rankingow zawodnikow obliczam roznice ich poziomu do wyliczenia spodziewanego wyniku partii (roznica 400 w rankingu to 10 razy wieksza szansa na zwyciestwo)
    double prawdopodobienstwo_wygranej_A = 1/(1 + pow(10,roznicaA)); //od 0 do 1

    double prawdopodobienstwo_wygranej_B = 1 - prawdopodobienstwo_wygranej_A;

    //a teraz porownam wynik rzeczywisty z prognozowanym i dostane wartosc o jaka zmieniam ranking
    if (kto_wygral == 1){
        ranking_uzyskanyA = floor(STALA*(1-prawdopodobienstwo_wygranej_A));
        ranking_uzyskanyB = floor(STALA*(0-prawdopodobienstwo_wygranej_B));

        rankingi = std::make_tuple(ranking_uzyskanyA, ranking_uzyskanyB);
        return rankingi;
    }else if (kto_wygral == 5) {
        ranking_uzyskanyA = floor(STALA*(0.5-prawdopodobienstwo_wygranej_A));
        ranking_uzyskanyB = floor(STALA*(0.5-prawdopodobienstwo_wygranej_B));

        rankingi = std::make_tuple(ranking_uzyskanyA, ranking_uzyskanyB);
        return rankingi;

    }else{ //czyli wygraly czarne
        ranking_uzyskanyA = floor(STALA*(0-prawdopodobienstwo_wygranej_A));
        ranking_uzyskanyB = floor(STALA*(1-prawdopodobienstwo_wygranej_B));

        rankingi = std::make_tuple(ranking_uzyskanyA, ranking_uzyskanyB);
        return rankingi;
    }
}

nlohmann::json wczytaj_jsona() {

    std::ifstream i(PLIK_Z_ZAWODNIKAMI);
    nlohmann::json zawodnicy;
    i >> zawodnicy;
    return zawodnicy;
}


void zapisz_jsona(const nlohmann::json &zawodnicy){

    std::ofstream o(PLIK_Z_ZAWODNIKAMI);
    o << std::setw(4) << zawodnicy << std::endl;
}


bool myfunction (const Zawodnik &i, const Zawodnik &j) {
    return (i.ranking >= j.ranking);
}


bool myfunction2 (const Zawodnik &i, const Zawodnik &j) {
    if (i.punkty>j.punkty) {
        return true;
    }else if (i.punkty<j.punkty) {
        return false;
    }else{
        return (i.buchholz>=j.buchholz);
    }
}




