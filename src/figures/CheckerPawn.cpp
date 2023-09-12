/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include "CheckerPawn.hpp"

CheckerPawn::CheckerPawn(bool isWhite) : Figure(isWhite)
{
    znakFigurky = 'p';
}

bool CheckerPawn::canIGoTo(Field *moveTo)
{
    if(pole == nullptr || moveTo == nullptr)
        return false;
    if(moveTo->isEmpty()){
        if(isWhite() || isKing()){
            if(pole->nextField(Direction::LU) == moveTo ||
               pole->nextField(Direction::RU) == moveTo)
                return true;
            if(pole->nextField(Direction::LU) != nullptr && pole->nextField(Direction::LU)->nextField(Direction::LU) == moveTo
                && !pole->nextField(Direction::LU)->isEmpty() && pole->nextField(Direction::LU)->get()->isWhite() != isWhite())
                return true;
            if(pole->nextField(Direction::RU) != nullptr && pole->nextField(Direction::RU)->nextField(Direction::RU) == moveTo
                && !pole->nextField(Direction::RU)->isEmpty() && pole->nextField(Direction::RU)->get()->isWhite() != isWhite())
                return true;
        }
        if(!isWhite() || isKing()){
            if(pole->nextField(Direction::LD) == moveTo ||
               pole->nextField(Direction::RD) == moveTo)
                return true;
            if(pole->nextField(Direction::LD) != nullptr && pole->nextField(Direction::LD)->nextField(Direction::LD) == moveTo
                && !pole->nextField(Direction::LD)->isEmpty() && pole->nextField(Direction::LD)->get()->isWhite() != isWhite())
                return true;
            if(pole->nextField(Direction::RD) != nullptr && pole->nextField(Direction::RD)->nextField(Direction::RD) == moveTo
                && !pole->nextField(Direction::RD)->isEmpty() && pole->nextField(Direction::RD)->get()->isWhite() != isWhite())
                return true;
        }
    }
    return false;
}


bool CheckerPawn::move(Field *moveTo)
{
    if(! canIGoTo(moveTo))
        return false;
    //Vyhození
    if(pole->nextField(Direction::LU) != nullptr && pole->nextField(Direction::LU)->nextField(Direction::LU) == moveTo)
        pole->nextField(Direction::LU)->remove(pole->nextField(Direction::LU)->get());
    else if(pole->nextField(Direction::LD) != nullptr && pole->nextField(Direction::LD)->nextField(Direction::LD) == moveTo)
        pole->nextField(Direction::LD)->remove(pole->nextField(Direction::LD)->get());
    else if(pole->nextField(Direction::RD) != nullptr && pole->nextField(Direction::RD)->nextField(Direction::RD) == moveTo)
        pole->nextField(Direction::RD)->remove(pole->nextField(Direction::RD)->get());
    else if(pole->nextField(Direction::RU) != nullptr && pole->nextField(Direction::RU)->nextField(Direction::RU) == moveTo)
        pole->nextField(Direction::RU)->remove(pole->nextField(Direction::RU)->get());

    pole->remove(this);
    moveTo->put(this);
    return true;
}

bool CheckerPawn::isKing()
{
    return znakFigurky == 'K';
}

void CheckerPawn::setKing(bool king)
{
    znakFigurky = king ? 'K' : 'p';
    pole->put(this);
}
