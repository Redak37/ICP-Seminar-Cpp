/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include "Board.hpp"

using namespace std;

Board::Board() {
    for(int i = 0; i < velikost; ++i){
        for(int j = 0; j < velikost; ++j){
            pole[j][i] = new Field(j,i);
        }
    }

    for(int s = 0; s < velikost; s++){
        for(int r = 0; r < velikost; r++){
            if(jeNaPlose(s, r-1))
                pole[s][r]->addNextField(Direction::D, pole[s][r-1]);
            if(jeNaPlose(s-1, r))
                pole[s][r]->addNextField(Direction::L, pole[s-1][r]);
            if(jeNaPlose(s-1, r-1))
                pole[s][r]->addNextField(Direction::LD, pole[s-1][r-1]);
            if(jeNaPlose(s-1, r+1))
                pole[s][r]->addNextField(Direction::LU, pole[s-1][r+1]);
            if(jeNaPlose(s+1, r))
                pole[s][r]->addNextField(Direction::R, pole[s+1][r]);
            if(jeNaPlose(s+1, r-1))
                pole[s][r]->addNextField(Direction::RD, pole[s+1][r-1]);
            if(jeNaPlose(s+1, r+1))
                pole[s][r]->addNextField(Direction::RU, pole[s+1][r+1]);
            if(jeNaPlose(s, r+1))
                pole[s][r]->addNextField(Direction::U, pole[s][r+1]);
        }
        }

}

Board::~Board() {
    for(int i = 0; i < velikost; ++i){
        for(int j = 0; j < velikost; ++j){
            delete pole[i][j];
        }
    }
}

bool Board::jeNaPlose(int s, int r){
       return s >= 0 && s < velikost && r >= 0 && r < velikost;
}

Field *Board::getField(int col, int row){
    if((unsigned int)(row -1) >= velikost || (unsigned int)(col -1) >= velikost)
        return NULL;
    return pole[col-1][row-1];
}
Field *Board::getField_normal(int col, int row){
    if((unsigned int)row >= velikost || (unsigned int)col >= velikost)
        return NULL;
    return pole[col][row];
}
int Board::getSize(){
    return velikost;
}
