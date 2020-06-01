//
// Created by albert on 23.06.19.
//

#include <limits>
#include "Partia.h"


Partia::Partia(std::size_t a, std::size_t b): kto_wygral{std::numeric_limits<std::size_t>::infinity()}
{
    czarne = a;
    biale = b;
//    std::numeric_limits<std::size_t>::max();
//    std::numeric_limits<std::size_t>::infinity();
}
