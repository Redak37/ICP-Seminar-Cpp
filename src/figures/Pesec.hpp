/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @brief Třída pro pěšce v šachu
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef FIGURES_PESEC_H_
#define FIGURES_PESEC_H_

#include "../Figure.hpp"

class Pesec: public Figure {
    public:

        /**
         * Vytvoří figurku dané barvy
         * @param isWhite - true pro bílou figurku, false pro černou
         */
        Pesec(bool isWhite);
        virtual ~Pesec();

        /** Funkce řekne, jestli figurka dokáže dojít na zadané políčko.
         *
         * @param moveTo - políčko, kam se má figurka pohnout
         * @return True, pokud se figurka může pohnout na toto políčko.
         */
        bool canIGoTo(Field *moveTo);

        /**
         * Funkce povýší pěšce na figurku identifikovanou jejím znakem. Provede výměnu na svém políčku.
         * @param naCo Znak povýšené figurky.
         * @return Vrací výslednou povýšenou figurku.
         */
        Figure *promote(char naCo);
};

#endif /* FIGURES_PESEC_H_ */
