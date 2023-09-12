#include "CheckersGame.hpp"

#include "../Figure.hpp"

#include <figures/CheckerPawn.hpp>

using namespace std;

CheckersGame::CheckersGame(Board *board, Adapter *adapter_p): Game(board, adapter_p)
{
    for (int i = 1; i <= 8; i+=2){
        figures.push_back(shared_ptr<Figure>(deska->getField(i, 1)->put(new CheckerPawn(true))));
    }
    for (int i = 2; i <=8; i+=2){
        figures.push_back(shared_ptr<Figure>(deska->getField(i, 2)->put(new CheckerPawn(true))));
    }
    for (int i = 1; i <= 8; i+=2){
        figures.push_back(shared_ptr<Figure>(deska->getField(i, 3)->put(new CheckerPawn(true))));
    }

    for (int i = 2; i <=8; i+=2){
        figures.push_back(shared_ptr<Figure>(deska->getField(i, 8)->put(new CheckerPawn(false))));
    }
    for (int i = 1; i <= 8; i+=2){
        figures.push_back(shared_ptr<Figure>(deska->getField(i, 7)->put(new CheckerPawn(false))));
    }
    for (int i = 2; i <=8; i+=2){
        figures.push_back(shared_ptr<Figure>(deska->getField(i, 6)->put(new CheckerPawn(false))));
    }
}

CheckersGame::~CheckersGame(){

}


bool CheckersGame::move(Figure *figure, Field *field, bool userMove){
    Field *pred = figure->getField();
    Figure *budeSebrana;
    if(pred->nextField(Direction::LU) == field ||
       pred->nextField(Direction::LD) == field ||
       pred->nextField(Direction::RU) == field ||
       pred->nextField(Direction::RD) == field)
        budeSebrana = nullptr;
    else{
        if(pred->nextField(Direction::LU) != nullptr && pred->nextField(Direction::LU)->nextField(Direction::LU) == field)
            budeSebrana = pred->nextField(Direction::LU)->get();
        else if(pred->nextField(Direction::LD) != nullptr && pred->nextField(Direction::LD)->nextField(Direction::LD) == field)
            budeSebrana = pred->nextField(Direction::LD)->get();
        else if(pred->nextField(Direction::RD) != nullptr && pred->nextField(Direction::RD)->nextField(Direction::RD) == field)
            budeSebrana = pred->nextField(Direction::RD)->get();
        else if(pred->nextField(Direction::RU) != nullptr && pred->nextField(Direction::RU)->nextField(Direction::RU) == field)
            budeSebrana = pred->nextField(Direction::RU)->get();
        else
            return false;
    }
    Field *polickoVyhozene;
    if(budeSebrana != nullptr)
        polickoVyhozene = budeSebrana->getField();
    bool pohnulSe = figure->move(field);
    string state = "";
    if(pohnulSe){
        if(figure->isWhite() == whiteOnMove){
            for(Tah move : tahy){
                if(move.figurka()->isWhite() == whiteOnMove){
                    move.setJumps(move.getJumps() + 1);
                }
                else{
                    break;
                }
            }
        }
        whiteOnMove = figure->isWhite();
        if(budeSebrana == nullptr){
            nextMoveWhite = !whiteOnMove;
        }
        else{
            bool neprosly = true;
            if(field->nextField(Direction::LU) != nullptr && figure->canIGoTo(field->nextField(Direction::LU)->nextField(Direction::LU)))
                neprosly = false;
            if(field->nextField(Direction::LD) != nullptr && figure->canIGoTo(field->nextField(Direction::LD)->nextField(Direction::LD)))
                neprosly = false;
            if(field->nextField(Direction::RU) != nullptr && figure->canIGoTo(field->nextField(Direction::RU)->nextField(Direction::RU)))
                neprosly = false;
            if(field->nextField(Direction::RD) != nullptr && figure->canIGoTo(field->nextField(Direction::RD)->nextField(Direction::RD)))
                neprosly = false;
            if(neprosly)
                nextMoveWhite = !whiteOnMove;
        }
        state = generateState(figure, pred, field);
        if(budeSebrana == nullptr)
            tahy.push_front(Tah(pred, figure, field, nullptr, nullptr, state, ((CheckerPawn *)figure)->isKing()));
        else
            tahy.push_front(Tah(pred, figure, field, budeSebrana, polickoVyhozene, state, ((CheckerPawn *)figure)->isKing()));
        if(figure->getChar() == 'p' && field->getRow() == (figure->isWhite() ? 7 : 0)){
            CheckerPawn *pesak = (CheckerPawn *) figure;
            pesak->setKing(true);
        }
        if(userMove){
            retahy.clear();
        }
    }
    return pohnulSe;
}


bool CheckersGame::undo(){
    if(tahy.empty())
        return false;
    Tah tah = tahy.front();
    tahy.pop_front();
    Figure *figurka = tah.figurka();
    ((CheckerPawn *) figurka)->setKing(tah.isKing());
    tah.setFigurka(tah.po()->get());
    retahy.push_front(tah);
    tah.po()->remove(tah.po()->get());
    tah.pred()->put(figurka);
    if(tah.druhaFigurka()!= nullptr)
        tah.polickoDruheFigurky()->put(tah.druhaFigurka());
    if(!tahy.empty() && tahy.front().getJumps() > 0)
        return undo();
    return true;
}

bool CheckersGame::redo(){
    if(retahy.empty())
        return false;
    Tah tah = retahy.front();
    retahy.pop_front();
    Figure *figurka = tah.figurka();
    if(tah.po()->getRow() == (figurka->isWhite() ? 7 : 0))
        ((CheckerPawn *) figurka)->setKing(true);
    tah.setFigurka(tah.pred()->get());
    tahy.push_front(tah);
    tah.pred()->remove(tah.pred()->get());
    tah.po()->put(figurka);
    if(tah.druhaFigurka()!= nullptr)
        tah.polickoDruheFigurky()->remove(tah.druhaFigurka());
    if(tah.getJumps() > 0)
        return redo();
    return true;
}


string CheckersGame::generateState(Figure *figure, Field *from, Field *to){
    string result = "";
    result += figure->getChar();
    result += (char)(from->getCol()+'a');
    result += to_string(from->getRow()+1) + (char)(to->getCol()+'a');
    result += to_string(to->getRow()+1);
    return result;
}
