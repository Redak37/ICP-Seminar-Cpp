/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include "Field.hpp"
#include "Figure.hpp"

using namespace std;

Field::Field(int col, int row) {
    sloupec = col;
    radek = row;
    kamen = NULL;
    adapter = NULL;
}

Field::~Field() {

}


void Field::setColRow(int s, int r){
    radek = r;
    sloupec = s;
}
int Field::getCol(){
    return sloupec;
}
int Field::getRow(){
    return radek;
}
void Field::addNextField(Direction dirs, Field *field){
    okoli[(int)dirs] = field;
}
Field *Field::nextField(Direction dirs){
    return okoli[(int) dirs];
}
Figure *Field::put(Figure *figure){
        kamen = figure;
        figure->setField(this);
        if(adapter)
            adapter->draw(radek, sloupec, figure->isWhite(), figure->getChar());
        return kamen;
}
bool Field::remove(Figure *figure){
    if(kamen != figure || !kamen)
        return false;
    kamen->setField(NULL);
    kamen = NULL;
    if(adapter)
        adapter->draw(radek, sloupec, false, ' ');
    return true;
}
bool Field::isEmpty(){
    if(kamen == NULL)
        return true;
    return false;
}
Figure *Field::get(){
    return kamen;
}

bool Field::equals(Field *f){
    return f == this;
}

void Field::setAdapter(Adapter *adapter_p){
    adapter = adapter_p;
}
