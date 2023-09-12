/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include "Pesec.hpp"
#include "Dama.hpp"
#include "Vez.hpp"
#include "Jezdec.hpp"
#include "Strelec.hpp"

using namespace std;

Pesec::Pesec(bool isWhite) : Figure(isWhite) {
   znakFigurky = 'p';
}

Pesec::~Pesec() {
}

bool Pesec::canIGoTo(Field *moveTo){
    if(pole == NULL)
        return false;
    Direction dopredu = (isWhite() ? Direction::U : Direction::D);
    Field *poleDalsi = pole->nextField(dopredu);
    if(muzeNa(moveTo) &&(
            (moveTo == poleDalsi && poleDalsi->isEmpty())
            || (moveTo == poleDalsi->nextField(Direction::R) && !poleDalsi->nextField(Direction::R)->isEmpty())
            || (moveTo == poleDalsi->nextField(Direction::L) && !poleDalsi->nextField(Direction::L)->isEmpty())
            || (moveTo == poleDalsi->nextField(dopredu) && poleDalsi->nextField(dopredu)->isEmpty() && poleDalsi->isEmpty() && pole->getRow() == (isWhite() ? 1 : 6))))
        return true;
    return false;
}

Figure *Pesec::promote(char naCo){
    Field *field = pole;
    pole->remove(this);
    Figure *fig = NULL;
    switch(naCo){
       case 'D':
           fig = new Dama(isWhite());
           break;
       case 'V':
           fig = new Vez(isWhite());
           break;
       case 'J':
           fig = new Jezdec(isWhite());
           break;
       case 'S':
           fig = new Strelec(isWhite());
           break;
    }
    field->put(fig);
    return fig;
}
