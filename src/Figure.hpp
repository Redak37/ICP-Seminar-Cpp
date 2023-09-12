/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef FIGURE_H_
#define FIGURE_H_

#include <cstdbool>
#include <string>
#include "Field.hpp"
/**
* @brief Třída pro figurky
*/
class Figure {
    public:
        /**
         * Vytvoří figurku dané barvy
         * @param isWhite - true pro bílou figurku, false pro černou
         */
        Figure(bool isWhite);
        virtual ~Figure();


        /**
         * @return True, pokud je figurka bílá.
         */
        bool isWhite();

        /**
         * @return Vrací znak reprezentující typ figurky
         */
        char getChar();

        /** Funkce pro nastavení políčka, na kterém se tenta figurka nachází. Null signalizuje, že se nenachází na žádném políčku.
         * @param field - nové políčko
         */
        void setField(Field *field);

        /**
         * @return Vrací políčko, na kterém stojí figurka.
         */
        Field *getField();

        /** Funkce která v základu otestuje pohyb na cíl přes canIGoTo a pak se pohne na cílové políčko a popřípadě vyhodí na něm stojící figurku.
         *
         * @param moveTo - políčko, kam se má figurka pohnout
         * @return True, pokud byl pohyb úspěšný.
         */
        virtual bool move(Field *moveTo);
        bool equals(Figure *f);


        /** Funkce implementovaná u každé figurky, která nám řekne, jestli figurka dokáže dojít na zadané políčko.
         *
         * @param moveTo - políčko, kam se má figurka pohnout
         * @return True, pokud se figurka může ponout na toto políčko.
         */
        virtual bool canIGoTo(Field *moveTo) = 0;


    private:
        bool jeBily;

    protected:
        Field *pole;
        char znakFigurky = 'X';


        /** Funkce pro kontrolu volné cesty
         * @pre políčka začátek a cíl patří do stejného boardu a leží ve stejném řádku, ve stejném sloupci nebo na diagonálách.
         * @param zacatek - počáteční políčko cesty
         * @param cil - koncové políčko cesty
         * @param smer - směr jakým máme cestovat
         * @return - Vrací true, pokud na cestě mezi začátkem a cílem v zadaném smětu leží figurka nebo je směr špatný, jinak vrací false.
         */
        bool kamenNaCeste(Field *zacatek, Field *cil, Direction smer);

        /** Funkce zkontroluje, zda zadané políčko je prázdné nebo na něm stojí figurka opačné barvy
         * Pouze pro ŠACHY
         * @param policko
         * @return true, pokud je políčko prázné nebo na něm stojí figurka opačné barvy
         */
        bool muzeNa(Field *policko);











};


#endif
