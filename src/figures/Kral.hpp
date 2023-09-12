/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @brief Třída pro krále v šachu
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef FIGURES_KRAL_H_
#define FIGURES_KRAL_H_

#include "../Figure.hpp"

/**
 * @brief Třída pro krále v šachu
 */
class Kral: public Figure {
    public:

        /**
         * Vytvoří figurku dané barvy
         * @param isWhite - true pro bílou figurku, false pro černou
         */
        Kral(bool isWhite);
        virtual ~Kral();

        /** Funkce řekne, jestli figurka dokáže dojít na zadané políčko.
         *
         * @param moveTo - políčko, kam se má figurka pohnout
         * @return True, pokud se figurka může pohnout na toto políčko.
         */
        bool canIGoTo(Field *moveTo);

    private:

};


#endif
