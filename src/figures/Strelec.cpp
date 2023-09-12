/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include <stdlib.h>
#include "Strelec.hpp"

using namespace std;

Strelec::Strelec(bool isWhite) : Figure(isWhite) {
   znakFigurky = 'S';
}

Strelec::~Strelec() {
}


bool Strelec::canIGoTo(Field *moveTo){
    if(pole == NULL || pole == moveTo || !muzeNa(moveTo))
        return false;
    int rozdilX = moveTo->getCol() - pole->getCol();
    int rozdilY = moveTo->getRow() - pole->getRow();
    if(abs(rozdilX) != abs(rozdilY)) // Cílové políčko neleží po diagonále od začátku
        return false;
    if(rozdilY > 0){
        if(rozdilX > 0){
            if(kamenNaCeste(pole, moveTo, Direction::RU))
                return false;
        }
        else if (rozdilX < 0){
            if(kamenNaCeste(pole, moveTo, Direction::LU))
                return false;
        }
    }
    else if(rozdilY < 0){
        if(rozdilX > 0){
            if(kamenNaCeste(pole, moveTo, Direction::RD))
                return false;
        }
        else if (rozdilX < 0){
            if(kamenNaCeste(pole, moveTo, Direction::LD))
                return false;
        }
    }
    return true;
}
