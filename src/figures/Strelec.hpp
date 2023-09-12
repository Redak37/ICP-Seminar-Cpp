/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @brief Třída pro střelce v šachu
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef FIGURES_STRELEC_H_
#define FIGURES_STRELEC_H_

#include "../Figure.hpp"

/**
 * @brief Třída pro střelce v šachu
 */
class Strelec: public Figure {
    public:
        /**
         * Vytvoří figurku dané barvy
         * @param isWhite - true pro bílou figurku, false pro černou
         */
        Strelec(bool isWhite);
        virtual ~Strelec();

        /** Funkce řekne, jestli figurka dokáže dojít na zadané políčko.
         *
         * @param moveTo - políčko, kam se má figurka pohnout
         * @return True, pokud se figurka může pohnout na toto políčko.
         */
        bool canIGoTo(Field *moveTo);
};

#endif /* FIGURES_STRELEC_H_ */
