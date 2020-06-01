//
// Created by albert on 22.06.19.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <ctime>
#include <math.h>
#include <tuple>

#include "json.hpp"

#include "Turniej.h"
#include "Runda.h"
#include "Zawodnik.h"

#include "funkcje.h"

#define RANKING 1000    //wartosc rankingu nowo dodanego zawodnika
#define STALA 32        //stala do wyliczania rankingow (im wieksza tym wieksze beda przyrosty za kazda wygrana)



Turniej::Turniej(): liczba_rund{0}
{
    std::cout << std::endl << "Wpisz nazwe turnieju " << std::endl;
    std::string nazwa;
    getline(std::cin, nazwa);
    nazwa_turnieju = nazwa;
}


void Turniej::stworz_zawodnikow() const {

    int b = 1;
    while(b){

        b = -1;
        while( b != 0 && b != 1) {
            std::cout << std::endl << "Jesli chcesz stworzyc zawodnika wpisz 1, a jesli juz wszyscy zapisani wpisz 0"
                      << std::endl;
            std::string b_str;
            std::cin >> b_str;
            std::cin.ignore();//bez tego jak za pierwszym razem zle wpisze to za nastepnym razem samo wpisuje imie :/
            try {
                b = std::stoi(b_str);
            }
            catch (std::invalid_argument &err) {
                std::cout << "Niepoprawne dane!" << std::endl;
            }
        }

        if(b) {
            //ZBIERAM DANE ZAWODNIKA DO PLIKU Z WSZYSTKIMI ZAWODIKAMI

            std::cout << std::endl << "Podaj imie " << std::endl;
            std::string imie;
            getline(std::cin, imie);
            std::cout << std::endl << "Podaj nazwisko " << std::endl;
            std::string nazwisko;
            getline(std::cin, nazwisko);

            int wiek = -1;
            while( wiek < 0 ) {
                std::cout << std::endl << "Podaj wiek " << std::endl;
                std::string wiek_str;
                std::cin >> wiek_str;
                try {
                    wiek = std::stoi(wiek_str);
                }
                catch(std::invalid_argument &err){
                   std::cout << "Niepoprawne dane!" << std::endl;
                }
            }

            int p = -1;
            while( p != 0 && p != 1) {
                std::cout << std::endl << "Wybierz plec: Mezczyzna wpisz 1, Kobieta wpisz 0 " << std::endl;

                std::string p_str;
                std::cin >> p_str;
                std::cin.ignore();
                try {
                    p = std::stoi(p_str);
                }
                catch (std::invalid_argument &err) {
                    std::cout << "Niepoprawne dane!" << std::endl;
                }
            }
            std::string plec;
            plec = (p) ? "Mezczyzna" : "Kobieta";

            //INNE DANE NP ILOSC PUNKTOW POTRZEBNE BEDA OSOBNO W ZALEZNOSCI OD DANEGO TURNIEJU (TO JUZ W OBIEKTACH KLASY ZAWODNIK)
            try {

                nlohmann::json zawodnicy = wczytaj_jsona();

                std::string imie_nazwisko = imie;
                imie_nazwisko.append(" ");
                imie_nazwisko.append(nazwisko);

                zawodnicy[imie_nazwisko]["Imie"] = imie;
                zawodnicy[imie_nazwisko]["Nazwisko"] = nazwisko;
                zawodnicy[imie_nazwisko]["Wiek"] = wiek;
                zawodnicy[imie_nazwisko]["Plec"] = plec;
                zawodnicy[imie_nazwisko]["Ranking"] = RANKING;

                //ZAPISZ ZAWODNIKA DO PLIKU
                zapisz_jsona(zawodnicy);
            }
            catch (nlohmann::detail::parse_error &err ) {
                nlohmann::json zawodnicy;
                zapisz_jsona(zawodnicy);
                std::cout << "UWAGA BRAKOWALO PLIKU "<< PLIK_Z_ZAWODNIKAMI << " " << std::endl << "Zostal utworzony, ale jest pusty!" << std::endl;
            }
        }
    }
}


void Turniej::dodaj_zawodnikow_do_turnieju() {

    int b = 1;
    while(b){

        b = -1;
        while( b != 0 && b != 1) {
            std::cout << std::endl
                      << "Jesli chcesz wczytac zawodnika z pliku do turnieju wpisz 1, jesli to juz wszyscy wpisz 0"
                      << std::endl;
            std::string b_str;
            std::cin >> b_str;
            std::cin.ignore();
            try {
                b = std::stoi(b_str);
            }
            catch (std::invalid_argument &err) {
                std::cout << "Niepoprawne dane!" << std::endl;
            }
        }

        try {
            if (b) {
                std::cout << std::endl << "Wpisz IMIE NAZWISKO zawodnika" << std::endl;
                std::string zawodnik_dodawany;
                getline(std::cin, zawodnik_dodawany);

                this->lista_zawodnikow.emplace_back(Zawodnik(zawodnik_dodawany));
            }
        }
        catch(nlohmann::detail::type_error &err ) {
            std::cout << "NIE MA TAKIEGO ZWODNIKA!" << std::endl;
        }
        catch(nlohmann::detail::parse_error &err){
            nlohmann::json zawodnicy;
            zapisz_jsona(zawodnicy);
            std::cout << "UWAGA BRAKOWALO PLIKU "<< PLIK_Z_ZAWODNIKAMI << " " << std::endl << "Zostal utworzony, ale jest pusty!" << std::endl;
        }
    }
    //GDY DODALEM JUZ WSZYSTKICH TO SPRAWDZE CZY KTOS NIE MUSI PAUZOWAC
    if(lista_zawodnikow.size()%2!=0){
        lista_zawodnikow.emplace_back( Zawodnik("pauza"));
    }
}


void Turniej::ustal_liczbe_rund() {

    if(lista_zawodnikow.size() > 8) {
        liczba_rund = 6;
    }else if (lista_zawodnikow.size()>1){
        liczba_rund = floor( log2(lista_zawodnikow.size()) );
    }
}

void Turniej::stworz_liste_startowa() {

    //najpierw ustawie liste startwowa wedlug rankingu
    std::sort (lista_zawodnikow.begin(), lista_zawodnikow.end(), myfunction);

    //Plik o nazwie Lista_Startowa_NAZWA TURNIEJU
    std::ofstream plik;
    std::string startowa = "dokumenty/Lista_Startowa_";
    startowa.append(nazwa_turnieju);

    plik.open(startowa);
    plik << "\t" << nazwa_turnieju << "\n";

    unsigned int numer = 0; //do przypisania numerow startowych

    for( auto &it : lista_zawodnikow ) {
        it.numer_startowy = numer;
        numer++;
        plik << it.imie << " " << it.nazwisko << " " << it.ranking << "\n";
    }
    plik.close();

    //symetryczna macierz w ktorej zaznaczam kto z kim gral
    kto_z_kim_gral.resize(lista_zawodnikow.size());
    for( auto &it : kto_z_kim_gral ) {
        it.resize(lista_zawodnikow.size());
    }

    for(std::size_t i=0; i< lista_zawodnikow.size(); i++ ) {      //sam ze soba nie mozesz grac wiec znaczam 1 (tak samo jak gdy juz z kims gralem)
        kto_z_kim_gral[i][i]=1;
    }

    std::cout<< std::endl << "Lista Startowa zostala utworzona!" << std::endl;
}


void Turniej::aktualizacja_danych_po_turnieju() const {

    //wczytuje zawodnikow z pliku
    nlohmann::json zawodnicy = wczytaj_jsona();

    for( const auto &it : lista_zawodnikow ) {

        zawodnicy[it.imie_nazwisko]["Ranking"] = it.ranking;

        std::string wynik = "Zdobyte miejsce: ";
        wynik.append(std::to_string(it.numer_startowy));
        wynik.append(".");

        zawodnicy[it.imie_nazwisko]["Historia wynikow "][nazwa_turnieju] = wynik;
    }

    zapisz_jsona(zawodnicy);
}


void Turniej::kojarzenie() {

    unsigned int ile_zawodnikow = lista_zawodnikow.size();

    unsigned int losowa1 = 0;
    unsigned int losowa2 = 0;
    bool poprawne = false;
    double ocena = 0;                                   //ocena kojarzenia: jest to KWADRAT SUMY ROZNIC punktow dobranych zawodnikow (chodzi o to by byla jak najmniesza, zeby lepsi zawodnicy grali z lepszymi, a slabsi ze slabszymi)
    double ocena_najlepsza = std::numeric_limits<double_t >::infinity();

    std::vector<unsigned int> sumy;                              //sumy poszczegolnych wierszy zeby sprawdzic czy wszystkie sa takie same --> czyli poprawne rozstawienie zawodnikow
    sumy.resize(ile_zawodnikow);

    std::vector<std::vector<std::size_t>> nowe_kojarzenie;      //macierz pomocnicza, to bedzie kopia kto_z_kim_gral w ktorym wyzn0acze kojarzenie nastepnej partii
    std::vector<std::vector<std::size_t>> najlepsze_kojarzenie; //bede ocenial kojarzenie i kopiowal do najlepszego jesli lepsze :-)

    unsigned int ile_razy = 100;
    if( ile_zawodnikow > 14){
        ile_razy = 10;//zeby bylo szybciej bo moze byc problem z ostatnimi
    }
    for( std::size_t oceniaj = 0; oceniaj<ile_razy; oceniaj++ ) {       //100razy znajduje losowe mozliwe kojarzenie i podmieniam jesli jest lepsze

        losowa1 = 0;
        losowa2 = 0;
        poprawne = false;

        while (!poprawne) {
            poprawne = true;

            nowe_kojarzenie.clear();
            nowe_kojarzenie.insert(nowe_kojarzenie.end(), kto_z_kim_gral.begin(), kto_z_kim_gral.end());

            for( std::size_t i = 0; i < ile_zawodnikow/2; i++ ) {
                std::size_t j = 0;
                while (nowe_kojarzenie[losowa1][losowa2] != 0) { // 0 znaczy ze moga ze soba grac, 1 grali, 2 oznaczam ze zagraja

                    j++;

                    if (j > 100000) {
                        i = 0;
                        losowa1 = 0;
                        losowa2 = 0;
                        poprawne = false; // 100.000 razy nie trafilem dobrze, moze to slepa uliczka... sprobojmy wiec od nowa! :-)
                        nowe_kojarzenie.clear();
                        nowe_kojarzenie.insert(nowe_kojarzenie.end(), kto_z_kim_gral.begin(), kto_z_kim_gral.end());
                        break;
                    }else {
                        //losuje indeksy zawodnikow ktorzy rozegraja partie razem
                        losowa1 = rd() % ile_zawodnikow;
                        losowa2 = rd() % ile_zawodnikow;
                    }
                }//znalazlem 0 czyli moga ze soba grac
                nowe_kojarzenie[losowa1][losowa2] = 2;  //2 oznacza ze wybralem ze bede z nim gral
                nowe_kojarzenie[losowa2][losowa1] = 2;
            }

            //sumuje wiersze kojrzenia
            for( std::size_t g = 0; g < ile_zawodnikow; g++ ) {
                sumy[g] = 0;
                for( std::size_t h = 0; h < ile_zawodnikow; h++ ) {
                    sumy[g] += nowe_kojarzenie[g][h];
                }
            }

            //jesli sumy sie roznia --> zle kojarzenie --> proboj od nowa!
            for( std::size_t g = 1; g < ile_zawodnikow; g++ ) {
                if (sumy[g] != sumy[0]) {
                    poprawne = false;
                }
            }
        }//JESLI STAD WYJDE ZNACZY ZE MAM KOJARZENIE


        //TUTAJ WYBIORE NAJLEPSZE KOJARZENIEEEE BEDE SPRAWDZAL I PODMIENIAL JESLI LEPSZE!

        for( std::size_t g = 0; g < ile_zawodnikow; g++ ) {
            for( std::size_t h = g; h < ile_zawodnikow; h++ ) {
                if (nowe_kojarzenie[g][h]==2) {
                    ocena += ( pow( ( lista_zawodnikow[g].punkty - lista_zawodnikow[h].punkty), 2)  ); // do kwadratu wiec wieksze roznice wiec dokladniej oraz pozbede sie ujemnych wartosci :-)
                }
            }
        }

        if (ocena < ocena_najlepsza ) {
            ocena_najlepsza = ocena;
            najlepsze_kojarzenie.clear();
            najlepsze_kojarzenie.insert(najlepsze_kojarzenie.end(), nowe_kojarzenie.begin(), nowe_kojarzenie.end());
        }
        if (ocena == 0) { //gdy ocena to 0 to jest na pewno najlepsze rozwiazanie, ale nie zawsze jest to mozliwe (ale np za pierwszym kojarzeniem turnieju zawsze bedzie 0)
            break;
        }
    }

    //Mam juz najlepssze kojarzenie wiec tworze obiekt rundy w ktorym powstana obiekty partii do ktorych bede mogl podac wyniki
    Runda nowa(najlepsze_kojarzenie, lista_zawodnikow);
    rundy.emplace_back(nowa);


    //trzeba odhaczyc ze planowane partie (2) juz sie odbyly (1)
    for( std::size_t h = 0; h < ile_zawodnikow; h++ ) {
        for( std::size_t g = h; g < ile_zawodnikow; g++ ) {
            if (najlepsze_kojarzenie[g][h] == 2) {
                kto_z_kim_gral[g][h] = 1;
                kto_z_kim_gral[h][g] = 1;
            }
        }
    }
}


void Turniej::wypisz_kojarzenie()const {
    std::cout<< std::endl << "Runda " << rundy[rundy.size()-1].numer_rundy << "." << std::endl;
    for( const auto it : rundy[rundy.size()-1].partie ) {
        std::cout<< "BIALE: " << lista_zawodnikow[it.biale].imie << " " << lista_zawodnikow[it.biale].nazwisko
                 << " CZARNE: " << lista_zawodnikow[it.czarne].imie  << " " << lista_zawodnikow[it.czarne].nazwisko << std::endl;
    }
}


void Turniej::wpisz_wyniki_rundy() {

    std::tuple <int, int> rankingi; //tutaj zgarne wartosci z funkcji oblicz_zdobyty_ranking

    std::cout<< std::endl;
    std::cout<< "Podaj wyniki partii: ";
    for( auto it : rundy[rundy.size()-1].partie ) {
        std::cout<< "BIALE: " << lista_zawodnikow[it.biale].imie << " " << lista_zawodnikow[it.biale].nazwisko
                 << " CZARNE: " << lista_zawodnikow[it.czarne].imie  << " " << lista_zawodnikow[it.czarne].nazwisko<< std::endl;
        std::cout<< std::endl;

        int kto_wygral = -1;
        while( kto_wygral != 0 && kto_wygral != 1 && kto_wygral != 5) {
            std::cout<< "Jesli wygraly biale wpisz 1, jesli czarne wpisz 0, jesli remis wpisz 5" << std::endl;
            std::string kto_str;
            std::cin >> kto_str;
            std::cin.ignore();
            try {
                kto_wygral = std::stoi(kto_str);
            }
            catch (std::invalid_argument &err) {
                std::cout << "Baranie jeden! Wybierz: 1, 5, 0" << std::endl;
            }
        }
        it.kto_wygral = kto_wygral;

        //ustawiam rankingi wzgledem rankingu ktory mieli gdy grali
        rankingi = oblicz_zdobyty_ranking(lista_zawodnikow[it.biale].ranking,lista_zawodnikow[it.czarne].ranking,it.kto_wygral);
        lista_zawodnikow[it.biale].ranking  += std::get<0>(rankingi);
        lista_zawodnikow[it.czarne].ranking += std::get<1>(rankingi);

        switch (it.kto_wygral) {
            case 1:
                lista_zawodnikow[it.biale].punkty++;
                break;
            case 0:
                lista_zawodnikow[it.czarne].punkty++;
                break;
            case 5:
                lista_zawodnikow[it.czarne].punkty += 0.5;
                lista_zawodnikow[it.biale].punkty += 0.5;
                break;
        }

        //uzupelniam tablice potrzebne do liczenia bucholca
        lista_zawodnikow[it.biale].przeciwnicy.emplace_back(it.czarne);
        lista_zawodnikow[it.czarne].przeciwnicy.emplace_back(it.biale);

        //Dopiero tutaj ustawiam preferencje koloru!
        lista_zawodnikow[it.czarne].kolor--;
        lista_zawodnikow[it.biale].kolor++;
    }
}


void Turniej::podglad() {
    std::cout<< std::endl;
    for( auto &it : lista_zawodnikow ){
        it.wypisz_informacje(); //ujemne rankingi sa zmieniane na 0!
    }
    std::cout<< std::endl;
}

void Turniej::wyniki_koncowe() {

    //DOPIERO TUTAJ NA KONIEC OBLICZAM BUCHOLCA
    for( auto &it : lista_zawodnikow ) {                                          //kazdemu zawodnikowi
        for( std::size_t i=0; i< it.przeciwnicy.size(); i++ ) {                           //po liscie swoich rywali
           it.buchholz += lista_zawodnikow[it.przeciwnicy[i]].punkty;             //zsumowac ich punkty
        }
    }

    std::sort (lista_zawodnikow.begin(), lista_zawodnikow.end(), myfunction2);    //zamieniam kolejnosc zawodnikow wiec juz wszystkie indeksy ktorych uzywalem sa nieaktualne!! dlatego wyniki dopiero na samym koncu

    //numer startowy juz nie potrzebny a wypisuje ladnie w klasie zawodik to go podmienie na pozycje w turnieju
    double pomocnicza = -1;  //bucholec poprzedniego zawodnika
    double pomocnicza2 = -1; //punkty poprzedniego zawodnika
    unsigned int pozycja = 1;
    bool powieksz = false; // bo jak dwe osobby maja to samo miejsce to trzeba zwiekszyc i nastepna bedzie dwie pozycje dalej
    for( auto &it : lista_zawodnikow ) {

        //posortowani sa ale moga miec punkty i bucholca rownego to trzeba im dac ta sama pozycje
        if (pomocnicza2==it.punkty && pomocnicza == it.buchholz) {
            pozycja--;
            powieksz = true;
         }
        it.numer_startowy = pozycja;
        pozycja++;
        pomocnicza = it.buchholz;
        pomocnicza2 = it.punkty;
        if (powieksz){
            pozycja++;
            powieksz = false;
        }
    }

    for( const auto &it : lista_zawodnikow ) {
        it.wypisz_informacje2();
    }
}


void Turniej::klasyfikacja() const{

    std::ofstream plik;
    std::string klasyfikacja = "dokumenty/Klasyfikacja_";
    klasyfikacja.append(nazwa_turnieju);
    plik.open(klasyfikacja);

    //wpisuje date
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    plik << (now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << '-' <<  now->tm_mday << "\n";

    //wpisuje wyniki zawodnikow
    plik << "\t" << nazwa_turnieju << "\n";
    plik << " Wyniki: \n";
    for( const auto &it : lista_zawodnikow ) {
        plik << it.numer_startowy << ". " << it.imie << " " << it.nazwisko<<" "<< it.punkty <<" "<< it.buchholz << " " << it.ranking << "\n";
    }
    plik << "\n\nProtokol wygenerowano przez program zaliczeniowy :-) ";

    plik.close();
    std::cout << std::endl << "Turniej zakonczony!" << std::endl;
}

void Turniej::start() {

    stworz_zawodnikow();                  //jesli jeszcze nie mam to dodaje sobie zawodnikow do pliku
    dodaj_zawodnikow_do_turnieju();       //wybieram zawodnikow ktorzy beda walczyc w turnieju
    ustal_liczbe_rund();                  //liczba rund zalezy od ilosci zawodnikow wiec po dodaniu wszystkich
    stworz_liste_startowa();              //Tworze plik txt w ktorym wypisane dane zawodnikow bioracych udzial w turnieju

    for( std::size_t i=0; i<liczba_rund; i++ ) {
        kojarzenie();                     //dobieram w pary
        wypisz_kojarzenie();              //sam komunikat
        wpisz_wyniki_rundy();             //pobieram od uzytkownika wyniki rundy
        podglad();                        //wypisuje dane zawodnikow dla sprawdzenia czy wszystko dziala jak powinno, przy okazji sprawdzam czy ranking nie jest ujemny, jesli tak to zeruje
    }
    wyniki_koncowe();                     //liczy bucholca, sortuje, wypisuje wyniki
    klasyfikacja();                       //zapisuje wyniki do pliku
    aktualizacja_danych_po_turnieju();    //na zakonczenie aby uaktualnic rankingi zawodnikow w plikach
}