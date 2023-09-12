/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include <fstream>
#include "Game.hpp"
#include "Parser.hpp"

using namespace std;

Parser::Parser(Game *hra)
{
    game = hra;
    deska = hra->getBoard();
}

void Parser::read(string fileName) {
    tahy.clear();
    ifstream vstup(fileName);
    if (vstup.is_open()){
        string tmp;
        while (getline (vstup,tmp))
        {
            if(!parse(tmp)){
                return;
            }
            tahy.push_back(tmp);
        }
        vstup.close();
    }

    while(game->undo()){
    }
}

bool Parser::parse(string radek) {
    QString qradek(radek.c_str());

    QStringList tmp = qradek.split(". ");

    if(tmp.length() != 2) {
        return false;
    }

    if(++cislo_tahu != tmp[0].toInt()) {
        return false;
    }

    tmp = tmp[1].split(" ");
    if(tmp.length() > 2) {
        return false;
    }

    QString figury[] = {"p", "V", "J", "S", "D", "K"};
    for(int ind = 0; ind < tmp.length(); ++ind) {
        int i = 0;
        int x = 0;
        int znakyNakonci = 0;
        bool prySach = false;
        char povysujeSeNa = 0;

        /*if(figury->contains(tmp[ind][0])) {
            i++;
        }*/
        for(auto k : figury){
            if(k.contains(tmp[ind][0]))
                i++;
        }

        char znakFigurky = (i == 1) ? (char)tmp[ind][0].cell() : 'p';

        if(tmp[ind].contains("x")) {
            ++x;
        }

        if(tmp[ind].contains("+")) {
            ++znakyNakonci;
            prySach = true;
        }
        if(tmp[ind].contains("#")) {
            ++znakyNakonci;
            if(prySach)
                return false;
            prySach = true;
        }

        for(auto k : figury){
            if(k.contains(tmp[ind][tmp[ind].length() - znakyNakonci - 1])){
                ++znakyNakonci;
                povysujeSeNa = (char)tmp[ind][tmp[ind].length() - znakyNakonci].cell();
            }
        }

        int delka = tmp[ind].length() - i - znakyNakonci - x;

        int row;
        int col;

        if (delka == 2) {
            col = tmp[ind][i+x].cell() - 'a' + 1;
            row = tmp[ind][i+x+1].cell() - '0';
            if(col < 1 || col > 8 || row < 1 || row > 8)
                return false;
            figurka = nullptr;
            pole_do = deska->getField(col, row);
            for(shared_ptr<Figure> fig_tmp : *game->getFigures()){
                Figure *fig = fig_tmp.get();
                if((fig->getChar() == znakFigurky) && (fig->canIGoTo(pole_do))){
                    if(figurka == nullptr){
                        figurka = fig;
                    }
                    else //žádné upřesnění
                        return false;
                }
            }
        } else if (delka == 3) {
            int prvni = tmp[ind][i+1].cell();
            if (prvni - 'a' < 0) {
                prvni -= '0';
                if(prvni < 1 || prvni > 8)
                    return false;
                figurka = nullptr;
                for(shared_ptr<Figure> fig_tmp : *game->getFigures()){
                    Figure *fig = fig_tmp.get();
                    if((fig->getChar() == znakFigurky) && (fig->getField()->getCol() == prvni -1)){
                        if(figurka == nullptr){
                            figurka = fig;
                        }
                        else //blbé upřesnění
                            return false;
                    }
                }
            } else {
                prvni -= 'a';
                if(prvni < 1 || prvni > 8)
                    return false;
                figurka = nullptr;
                for(shared_ptr<Figure> fig_tmp : *game->getFigures()){
                    Figure *fig = fig_tmp.get();
                    if((fig->getChar() == znakFigurky) && (fig->getField()->getRow() == prvni -1)){
                        if(figurka == nullptr){
                            figurka = fig;
                        }
                        else //blbé upřesnění
                            return false;
                    }
                }
            }
            col = tmp[ind][i+x+1].cell() - 'a' + 1;
            row = tmp[ind][i+x+2].cell() - '0';
        } else if(delka == 4) {
            col = tmp[ind][i].cell() - 'a' + 1;
            row = tmp[ind][i+1].cell() - '0';
            if(col < 1 || col > 8 || row < 1 || row > 8)
                return false;
            figurka = deska->getField(col, row)->get();
            col = tmp[ind][i+x+2].cell() - 'a' + 1;
            row = tmp[ind][i+x+3].cell() - '0';
        } else {
            return false;
        }

        if(col < 1 || col > 8 || row < 1 || row > 8)
            return false;
        pole_do = deska->getField(col, row);
        char savePrevious = game->getPromoteTo();
        if(povysujeSeNa != 0)
            game->setPromoteTo(povysujeSeNa);
        if(!game->move(figurka, pole_do))
            return false;
        game->setPromoteTo(savePrevious);
        if(game->byloVyhozeni() != (x == 1))
            return false;
        if(game->getCheck() != prySach)
            return false;
    }
    return true;
}

vector<string> Parser::getMoves(){
    return tahy;
}
