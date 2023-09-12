/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include "Game.hpp"
#include "figures/Pesec.hpp"

using namespace std;

Game::Game(Board *board, Adapter *adapter_p) {
    if(board){
        deska = board;
    } else {
        destroyBoard = true;
        deska = new Board();
    }

    adapter = adapter_p;

    for(int j = 0; j < 8; ++j)
        for(int i = 0; i < 8; ++i){
            Field *f = deska->getField_normal(j,i);
            f->setAdapter(adapter);
    }
}

Game::~Game() {
    if(destroyBoard)
        delete deska;
}




bool Game::move(Figure *figure, Field *field){
    return move(figure, field, false);
}

Board *Game::getBoard(){
    return deska;
}
bool Game::getCheck(){
    return check;
}

bool Game::byloVyhozeni(){
    return vyhozeni;
}

std::vector<std::shared_ptr<Figure>> *Game::getFigures(){
    return &figures;
}

std::deque<Tah> *Game::getMoves(){
    return &tahy;
}

std::deque<Tah> *Game::getRedoMoves(){
    return &retahy;
}

 void Game::setPromoteTo(char to){
     promoteTo = to;
 }

 char Game::getPromoteTo()
 {
     return promoteTo;
 }

 bool Game::isNextWhite()
 {
     return nextMoveWhite;
 }
