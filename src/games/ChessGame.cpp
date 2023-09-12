#include "ChessGame.hpp"

#include <vector>
#include <stack>
#include <cstdbool>
#include <memory>

#include "Tah.hpp"

#include "../Figure.hpp"
#include "../figures/Kral.hpp"
#include "../figures/Dama.hpp"
#include "../figures/Jezdec.hpp"
#include "../figures/Pesec.hpp"
#include "../figures/Strelec.hpp"
#include "../figures/Vez.hpp"

using namespace std;

ChessGame::ChessGame(Board *board, Adapter *adapter_p): Game(board, adapter_p)
{
    figures.push_back(shared_ptr<Figure>(deska->getField(1, 1)->put(new Vez(true))));
    figures.push_back(shared_ptr<Figure>(deska->getField(8, 1)->put(new Vez(true))));
    figures.push_back(shared_ptr<Figure>(deska->getField(2, 1)->put(new Jezdec(true))));
    figures.push_back(shared_ptr<Figure>(deska->getField(7, 1)->put(new Jezdec(true))));
    figures.push_back(shared_ptr<Figure>(deska->getField(3, 1)->put(new Strelec(true))));
    figures.push_back(shared_ptr<Figure>(deska->getField(6, 1)->put(new Strelec(true))));
    figures.push_back(shared_ptr<Figure>(deska->getField(4, 1)->put(new Dama(true))));
    figures.push_back(shared_ptr<Figure>(deska->getField(5, 1)->put(new Kral(true))));
    for(int i = 1; i <= 8; i++){
        figures.push_back(shared_ptr<Figure>(deska->getField(i, 2)->put(new Pesec(true))));
    }

    figures.push_back(shared_ptr<Figure>(deska->getField(1, 8)->put(new Vez(false))));
    figures.push_back(shared_ptr<Figure>(deska->getField(8, 8)->put(new Vez(false))));
    figures.push_back(shared_ptr<Figure>(deska->getField(2, 8)->put(new Jezdec(false))));
    figures.push_back(shared_ptr<Figure>(deska->getField(7, 8)->put(new Jezdec(false))));
    figures.push_back(shared_ptr<Figure>(deska->getField(3, 8)->put(new Strelec(false))));
    figures.push_back(shared_ptr<Figure>(deska->getField(6, 8)->put(new Strelec(false))));
    figures.push_back(shared_ptr<Figure>(deska->getField(4, 8)->put(new Dama(false))));
    figures.push_back(shared_ptr<Figure>(deska->getField(5, 8)->put(new Kral(false))));
    for(int i = 1; i <= 8; i++){
        figures.push_back(shared_ptr<Figure>(deska->getField(i, 7)->put(new Pesec(false))));
    }

}

ChessGame::~ChessGame(){

}


bool ChessGame::move(Figure *figure, Field *field, bool userMove){
    check = false;
    vyhozeni = false;
    Field *pred = figure->getField();
    Figure *budeSebrana = field->get();
    vyhozeni = budeSebrana != nullptr;
    bool pohnulSe = figure->move(field);
    string state = "";
    if(pohnulSe){
        if(!figure->isWhite())
            cisloTahu++;
        state = generateState(figure, pred, field, vyhozeni, '\0');
        if(figure->getChar() == 'p' && figure->getField()->getRow() == (figure->isWhite() ? 7 : 0)){
            Pesec *pesak = (Pesec*) figure;
            //TODO char povýšení
            figure = pesak->promote(promoteTo);
            figures.push_back(shared_ptr<Figure>(figure));
        }
    }
    Figure *mujKral = nullptr;
    Figure *enemyKral = nullptr;
    for(shared_ptr<Figure>fig_tmp : figures){
        Figure *fig = fig_tmp.get();
        if (fig->getChar() == 'K' && fig->isWhite() == figure->isWhite()){
            mujKral = fig;
        }
        if (fig->getChar() == 'K' && fig->isWhite() != figure->isWhite()){
            enemyKral = fig;
        }
    }
    for(shared_ptr<Figure>fig_tmp : figures){
        Figure *fig = fig_tmp.get();
        if(fig->canIGoTo(mujKral->getField())){
            tahy.push_front(Tah(pred, figure, field, budeSebrana, nullptr, ""));
            undo();
            retahy.pop_front();
            pohnulSe = false;
            //TODO zobrazit seš kkt
        }
    }
    for(shared_ptr<Figure>fig_tmp : figures){
        Figure *fig = fig_tmp.get();
        if(fig->canIGoTo(enemyKral->getField())){
            //TODO zobrazit šach
            check = true;
        }
    }
    if(check)
        state += "+";
    if(pohnulSe){
        tahy.push_front(Tah(pred, figure, field, budeSebrana, nullptr, state));
        if(userMove){
            while(!retahy.empty())
                retahy.pop_front();
        }
    }
    return pohnulSe;
}


bool ChessGame::undo(){
    if(tahy.empty())
        return false;
    Tah tah = tahy.front();
    tahy.pop_front();
    Figure *figurka = tah.figurka();
    if(!figurka->isWhite())
            cisloTahu--;
    tah.setFigurka(tah.po()->get());
    retahy.push_front(tah);
    tah.po()->remove(tah.po()->get());
    tah.pred()->put(figurka);
    if(tah.druhaFigurka()!= nullptr)
            tah.po()->put(tah.druhaFigurka());
    return true;
}

bool ChessGame::redo(){
    if(retahy.empty())
        return false;
    Tah tah = retahy.front();
    retahy.pop_front();
    Figure *figurka = tah.figurka();
    if(!figurka->isWhite())
            cisloTahu++;
    tah.setFigurka(tah.pred()->get());
    tahy.push_front(tah);
    tah.pred()->remove(tah.pred()->get());
    tah.po()->put(figurka);
    return true;
}


string ChessGame::generateState(Figure *figure, Field *from, Field *to, bool vyhozeni, char povyseni){
    string result = figure->isWhite() ? to_string(cisloTahu) + ". " : " ";
    result += (char)(figure->getChar());
    result += (char)(from->getCol()+'a');
    result += (to_string(from->getRow() + 1));
    if(vyhozeni)
        result += "x";
    result += ((char)(to->getCol()+'a'));
    result += (to_string(to->getRow() + 1));
    if(povyseni != '\0'){
        result += povyseni;
    }
    return result;
}
