/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @brief Třída pro figurku v checkers (pěšáka i jeho povýšenou podobu)
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef CHECKERPAWN_HPP
#define CHECKERPAWN_HPP

#include <Figure.hpp>



class CheckerPawn: public Figure
{
    public:

        /**
         * Vytvoří figurku dané barvy
         * @param isWhite - true pro bílou figurku, false pro černou
         */
        CheckerPawn(bool isWhite);

        /** Funkce řekne, jestli figurka dokáže dojít na zadané políčko.
         *
         * @param moveTo - políčko, kam se má figurka pohnout
         * @return True, pokud se figurka může ponout na toto políčko.
         */
        bool canIGoTo(Field *moveTo);

        /**
         * @return Vrátí, zda je tato figurka Král
         */
        bool isKing();

        /**
         * Nastaví, zda je tato figurka král. Změní znak, který ji reprezentuje.
         * @param king true pokud se má figurka stát králem
         */
        void setKing(bool king);

        /** Funkce která v základu otestuje pohyb na cíl přes canIGoTo a pak se pohne na cílové políčko a popřípadě vyhodí přeskočené figurky.
         *
         * @param moveTo - políčko, kam se má figurka pohnout
         * @return True, pokud byl pohyb úspěšný.
         */
        bool move(Field *moveTo);
};

#endif // CHECKERPAWN_HPP
