/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include <stdlib.h>
#include "Dama.hpp"

using namespace std;

Dama::Dama(bool isWhite) : Figure(isWhite) {
   znakFigurky = 'D';
}

Dama::~Dama() {
}


bool Dama::canIGoTo(Field *moveTo){
    if(pole == NULL || pole == moveTo || !muzeNa(moveTo))
        return false;
    int rozdilX = moveTo->getCol() - pole->getCol();
    int rozdilY = moveTo->getRow() - pole->getRow();
    if(pole->getCol() == moveTo->getCol() || pole->getRow() == moveTo->getRow()){ //jako věž
        if(pole->getCol() == moveTo->getCol()){
            int rozdil = pole->getRow() - moveTo->getRow();
            if(rozdil > 0){ //cílové políčko je menší -> přesun dolů
                if(kamenNaCeste(pole, moveTo, Direction::D))
                    return false;
            }
            else if(rozdil < 0){ //přesun nahoru
                if(kamenNaCeste(pole, moveTo, Direction::U))
                    return false;
            }
        }
        else if(pole->getRow() == moveTo->getRow()){
            int rozdil = pole->getCol() - moveTo->getCol();
            if(rozdil > 0){ //cílové políčko je menší -> přesun doleva
                if(kamenNaCeste(pole, moveTo, Direction::L))
                    return false;
            }
            else if(rozdil < 0){ //přesun doprava
                if(kamenNaCeste(pole, moveTo, Direction::R))
                    return false;
            }
        }
    }
    else if(abs(rozdilX) == abs(rozdilY)){ //jako střelec
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
    }
    else{
        return false;
    }
    return true;
}
