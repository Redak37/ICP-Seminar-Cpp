/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef BOARD_H_
#define BOARD_H_

#include <cstdbool>
#include <vector>

#include "Field.hpp"
#include "Adapter.hpp"

/**
 * @brief Třída pro šachovnici
 */
class Board {
    public:
        /**
         * @brief Vytvoří hrací desku s políčkami
         * @param size - velikost čtvercové desky
         */
        Board();
        virtual ~Board();

        /**
         * @brief Vrátí políčko na daných souřadnicích, zadáváno 1-8
         * @param col - sloupec
         * @param row - řádek
         * @return políčko na souřadnicích
         */
        Field *getField(int col, int row);

        /**
         * @brief Vrátí políčko na daných souřadnicích, zadáváno 0-7
         * @param col - sloupec
         * @param row - řádek
         * @return políčko na souřadnicích
         */
        Field *getField_normal(int col, int row);
        int getSize();

    private:
        int velikost = 8;
        Field *pole[8][8];
        /**
         * @brief Funkce kontroluje, zda se políčko se zadanými indexy nachází na hrací ploše nebo je mimo
         * @param s - sloupec
         * @param r - řádek
         * @return - funkce vrací true, pokud indexy políčka spadají do hrací plochy, jinak vrací false
         */
        bool jeNaPlose(int s, int r);
};


#endif
