/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @brief Třída pro věž v šachu
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef FIGURES_VEZ_H_
#define FIGURES_VEZ_H_

#include "../Figure.hpp"

class Vez: public Figure {
    public:

        /**
         * Vytvoří figurku dané barvy
         * @param isWhite - true pro bílou figurku, false pro černou
         */
        Vez(bool isWhite);
        virtual ~Vez();

        /** Funkce řekne, jestli figurka dokáže dojít na zadané políčko.
         *
         * @param moveTo - políčko, kam se má figurka pohnout
         * @return True, pokud se figurka může pohnout na toto políčko.
         */
        bool canIGoTo(Field *moveTo);
};

#endif /* FIGURES_VEZ_H_ */
