/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include "Figure.hpp"

using namespace std;

Figure::Figure(bool isWhite){
    jeBily = isWhite;
    pole = NULL;
}

Figure::~Figure(){

}

bool Figure::isWhite(){
    return jeBily;
}
char Figure::getChar(){
    return znakFigurky;
}
void Figure::setField(Field *field){
    pole = field;
}
Field *Figure::getField(){
    return pole;
}
bool Figure::move(Field *moveTo){
    if(! canIGoTo(moveTo))
        return false;
    pole->remove(this);
    moveTo->remove(moveTo->get()); //toto nám zajistí správně fungující vyhazování
    moveTo->put(this);
    return true;
}

bool Figure::kamenNaCeste(Field *zacatek, Field *cil, Direction smer){
        while((zacatek = zacatek->nextField(smer)) != cil){
            if (zacatek == NULL)
                return true; //Pokud figurka uteče z plochy, tak do cíle tímto směrem nedojde
            if(!zacatek->isEmpty())
                return true; //políčko není prázdné - něco je mezi zdrojovým a cílovým = konec
        }
        return false;
    }

    /** Funkce zkontroluje, zda zadané políčko je prázdné nebo na něm stojí figurka opačné barvy
     *
     * @param policko
     * @return true, pokud je políčko prázné nebo na něm stojí figurka opačné barvy
     */
bool Figure::muzeNa(Field *policko){
        bool result = policko->isEmpty() || policko->get()->isWhite() != this->isWhite();
        return result;
}

bool Figure::equals(Figure *f){
    return f == this;
}
