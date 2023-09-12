/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include "Kral.hpp"

using namespace std;

Kral::Kral(bool isWhite) : Figure(isWhite) {
   znakFigurky = 'K';
}

Kral::~Kral() {

}

bool Kral::canIGoTo(Field *moveTo){
    return muzeNa(moveTo) && (moveTo == pole->nextField(Direction::D) || moveTo == pole->nextField(Direction::L) || moveTo == pole->nextField(Direction::LD)
    || moveTo == pole->nextField(Direction::LU) || moveTo == pole->nextField(Direction::R) || moveTo == pole->nextField(Direction::RD)
    || moveTo == pole->nextField(Direction::RU) || moveTo == pole->nextField(Direction::U));
}
