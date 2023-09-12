/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include "Jezdec.hpp"

using namespace std;

Jezdec::Jezdec(bool isWhite) : Figure(isWhite) {
   znakFigurky = 'J';
}

Jezdec::~Jezdec() {
}

bool Jezdec::canIGoTo(Field *moveTo){
    if(pole == NULL)
        return false;
    Field *levyhorni = pole->nextField(Direction::LU);
    Field *pravyhorni = pole->nextField(Direction::RU);
    Field *levydolni = pole->nextField(Direction::LD);
    Field *pravdydolni = pole->nextField(Direction::RD);

    if(muzeNa(moveTo) && ((levyhorni != NULL && (levyhorni->nextField(Direction::U) == moveTo || levyhorni->nextField(Direction::L) == moveTo))
    || (pravyhorni != NULL && (pravyhorni->nextField(Direction::U) == moveTo || pravyhorni->nextField(Direction::R) == moveTo))
    || (levydolni != NULL && (levydolni->nextField(Direction::D) == moveTo || levydolni->nextField(Direction::L) == moveTo))
    || (pravdydolni != NULL && (pravdydolni->nextField(Direction::D) == moveTo || pravdydolni->nextField(Direction::R) == moveTo))))
        return true;
    return false;
}
