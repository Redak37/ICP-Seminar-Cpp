/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @brief Třída pro královnu v šachu
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */

#ifndef FIGURES_DAMA_H_
#define FIGURES_DAMA_H_

#include "../Figure.hpp"

class Dama: public Figure {
    public:

        /**
         * Vytvoří figurku dané barvy
         * @param isWhite - true pro bílou figurku, false pro černou
         */
        Dama(bool isWhite);
        virtual ~Dama();

        /** Funkce řekne, jestli figurka dokáže dojít na zadané políčko.
         *
         * @param moveTo - políčko, kam se má figurka pohnout
         * @return True, pokud se figurka může pohnout na toto políčko.
         */
        bool canIGoTo(Field *moveTo);
};

#endif /* FIGURES_DAMA_H_ */
