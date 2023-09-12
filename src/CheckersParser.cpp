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
#include "CheckersParser.hpp"

using namespace std;

CheckersParser::CheckersParser(Game *hra)
{
    game = hra;
    deska = hra->getBoard();
}

void CheckersParser::read(string fileName) {
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

bool CheckersParser::parse(string radek) {
    QString qradek(radek.c_str());

    QStringList tmp = qradek.split(". ");

    if(tmp.length() != 2) {
        return false;
    }

    if(++cislo_tahu != tmp[0].toInt()) {
        return false;
    }

    tmp = tmp[1].split(" ");
    for (QString part : tmp) {
        if (part.length() != 5)
            return false;
        Figure *figurka;
        Field *policko;
        int row;
        int col;

        col = part[1].cell() - 'a' + 1;
        row = part[2].cell() - '0';
        if(col < 1 || col > 8 || row < 1 || row > 8)
            return false;
        figurka = deska->getField(col, row)->get();
        col = part[3].cell() - 'a' + 1;
        row = part[4].cell() - '0';
        if(col < 1 || col > 8 || row < 1 || row > 8)
            return false;
        policko = deska->getField(col, row);
        if(!game->move(figurka, policko))
            return false;
    }
    return true;
}

vector<string> CheckersParser::getMoves(){
    return tahy;
}
