/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef TAH_H_
#define TAH_H_

#include "Field.hpp"
#include "Figure.hpp"
#include <string>

/**
 * @brief The Tah class
 */
class Tah {
    public:
         /**
         * @brief Uloží tah
         * @param pred - Políčko na které stála figurka před pohybem.
         * @param figurka - Figurka, která se hýbe
         * @param po - Políčko kam se táhlo.
         * @param druhaFigurka - Vyhozená figurka nebo druhá figurka rošády.
         * @param polickoDruheFigurky - Políčko vyhozené figurky, pokud není shodné s cílovým políčkem.
         * @param state - Textová reprezentace tohoto tahu
         * @param king - zda byla figurka v Checkers před provedením tahu král. Pouze Checkers
         */
        Tah(Field *pred, Figure *figurka, Field *po, Figure *druhaFigurka, Field *polickoDruheFigurky, std::string state, bool king = false);
        virtual ~Tah();

        /**
         * @return Vrací políčko na které stála figurka před pohybem.
         */
        Field *pred();
        /**
         * @return Vrací políčko kam se táhlo.
         */
        Field *po();
        /**
         * @return Vrátí figurku se kterou se táhlo. V případě povyšování pěšce.
         */
        Figure *figurka();
        /**
         * Nastaví figurku tahu
         * @param figurka
         */
        void setFigurka(Figure *figurka);
        /**
         * @return Vrátí druhou figurku (vyhozenou).
         */
        Figure *druhaFigurka();
        /**
         * @return Vrátí políčko druhou figurky pokud se liší od cílového.
         */
        Field *polickoDruheFigurky();
        /**
         * @return Vrátí textovou reprezentaci tahu
         */
        std::string getState();
        /**
         * Nastaví textovou reprezentaci tahu
         * @param state
         */
        void setState(std::string x);
        /**
         * @return Vrátí kolikrát se už v tomto tahu skočilo. Pouze Checkers
         */
        int getJumps();
        /**
         * Nastaví kolikrát se už v tomto tahu skočilo. Pouze Checkers
         * @param jumps
         */
        void setJumps(int jumps);
        /**
         * @return Vrátí, zda figurka je král. Pouze Checkers
         */
        bool isKing();

    private:
        Field *pred_a;
        Figure *figurka_a;
        Field *po_a;
        Figure *druhaFigurka_a;
        Field *polickoDruheFigurky_a;
        std::string state_a;
        int jumpCount = 0;
        bool king = false;
};


#endif
