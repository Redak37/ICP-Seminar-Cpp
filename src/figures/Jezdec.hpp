/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @brief Třída pro jezdce v šachu
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef FIGURES_KUN_H_
#define FIGURES_KUN_H_

#include "../Figure.hpp"

class Jezdec: public Figure {
    public:

        /**
         * Vytvoří figurku dané barvy
         * @param isWhite - true pro bílou figurku, false pro černou
         */
        Jezdec(bool isWhite);
        virtual ~Jezdec();

        /** Funkce řekne, jestli figurka dokáže dojít na zadané políčko.
         *
         * @param moveTo - políčko, kam se má figurka pohnout
         * @return True, pokud se figurka může pohnout na toto políčko.
         */
        bool canIGoTo(Field *moveTo);
};

#endif /* FIGURES_KUN_H_ */
