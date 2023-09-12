/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include "Vez.hpp"

using namespace std;

Vez::Vez(bool isWhite) : Figure(isWhite) {
   znakFigurky = 'V';
}

Vez::~Vez() {
}

bool Vez::canIGoTo(Field *moveTo){
    if(pole == NULL || pole == moveTo || !muzeNa(moveTo))
       return false;
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
   else
       return false;
   return true;
}
