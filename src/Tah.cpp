/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include "Tah.hpp"

using namespace std;

Tah::Tah(Field *pred, Figure *figurka, Field *po, Figure *druhaFigurka, Field *polickoDruheFigurky, std::string state, bool king){
    this->pred_a = pred;
    this->figurka_a = figurka;
    this->po_a = po;
    this->druhaFigurka_a = druhaFigurka;
    this->polickoDruheFigurky_a = polickoDruheFigurky;
    this->state_a = state;
    this->king = king;
}

Tah::~Tah() {

}


Field *Tah::pred(){
    return pred_a;
}

Field *Tah::po(){
    return po_a;
}

Figure *Tah::figurka(){
    return figurka_a;
}

void Tah::setFigurka(Figure *figurka){
    this->figurka_a = figurka;
}

Figure *Tah::druhaFigurka(){
    return druhaFigurka_a;
}

Field *Tah::polickoDruheFigurky(){
    return polickoDruheFigurky_a;
}

std::string Tah::getState(){
    return state_a;
}
void Tah::setState(std::string x){
    state_a = x;
}

int Tah::getJumps()
{
    return jumpCount;
}

void Tah::setJumps(int jumps)
{
    jumpCount = jumps;
}

bool Tah::isKing()
{
    return king;
}
