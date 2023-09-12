/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef FIELD_H_
#define FIELD_H_

#include <cstdbool>
#include <stdlib.h>
#include "Adapter.hpp"

class Figure;

/**
 * @brief Enum specifikující 8 směrů okolí políčka
 */
enum class Direction{
    LU, U, RU, L, R, LD, D, RD
};

/**
 * @brief Třída pro jednotlivá pole šachovnice
 */
class Field {
    public:
        /**
         * @brief Vytvoří políčko, které si zapamatuje, že leží na daných souřadnicích
         * @param col 0-7
         * @param row 0-7
         */
        Field(int col, int row);
        virtual ~Field();

        /**
         * @brief Nastaví sloupec a řádek políčka
         * @param s
         * @param r
         */
        void setColRow(int s, int r);

        /**
         * @return - Funkce vrací číslo sloupce políčka počítáno od 0
         */
        int getCol();

        /**
         * @return - Funkce vrací číslo řádku políčka počítáno od 0
         */
        int getRow();

        /**
         * @brief Funkce přidá políčku souseda v daném směru.
         * @param dirs směr
         * @param field sousední políčko
         */
        void addNextField(Direction dirs, Field *field);

        /**
         * @param dirs směr
         * @return - Funkce vrátí sousední políčko tohoto políčka v zadaném směru
         */
        Field *nextField(Direction dirs);

        /**
         * @brief Položí figurku na toto políčko
         * @param figure - figurka
         * @return - vrací předanou figurku
         */
        Figure *put(Figure *figure);

        /**
         * @brief Odstraní konkrétní figurku z políčka
         * @param figure - figurka
         * @return - true, pokud předaná figurka byla odstraněna
         */
        bool remove(Figure *figure);

        /**
         * @return - True, pokud je políčko prázdné = nestojí na něm figurka.
         */
        bool isEmpty();

        /**
         * @return Vrací figurka, která stojí na políčku. Null pokud na něm nic nestojí.
         */
        Figure *get();

        /**
         * @return Vrací true, pokud jsou dvě políčka rovny.
         */
        bool equals(Field *f);

        /**
         * @brief Nastaví adaptér políčku
         * @param adapter_p
         */
        void setAdapter(Adapter *adapter_p);

    private:
        int radek;
        int sloupec;
        Figure *kamen;
        Field  *okoli[8] = {0};
        Adapter *adapter;

};


#endif
