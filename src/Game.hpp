/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <deque>
#include <cstdbool>
#include <memory>

#include "Board.hpp"
#include "Tah.hpp"
#include "Figure.hpp"
#include "Field.hpp"
#include "Adapter.hpp"

/**
 * @brief Abstraktní třída pro jednotlivé hry
 */
class Game {
    public:
        /**
         * @brief Vytvoří hru se zadanou deskou.
         * @param board
         */
        Game(Board *board, Adapter *adapter_p);
        virtual ~Game();


        /**
         * @brief Provede pohyb s figurkou na políčko.
         * @param figure - hýbaná figurka
         * @param field - cílové políčko
         * @param userMove - true, pokud se jedná o tah, který provedl uživatel. V tomto případě se vyprázdní vektor retahů pro redo()
         * @return true, pokud byl pohyb úspěšný
         */
        virtual bool move(Figure *figure, Field *field, bool userMove) = 0;

        /**
         * @brief Vrátí předchozí tah.
         * @return True, pokud se undo provedlo (zásobník tahů nebyl prázdný)
         */
        virtual bool undo() = 0;

        /**
         * @brief Znovu provede vrácený tah.
         * @return True, pokud se redo provedlo (zásobník retahů nebyl prázdný)
         */
        virtual bool redo() = 0;

        /**
         * @brief Provede pohyb s figurkou na políčko.
         * @param figure - hýbaná figurka
         * @param field - cílové políčko
         * @return true, pokud byl pohyb úspěšný
         */
        bool move(Figure *figure, Field *field);

        /**
         * @return Vrací desku této hry.
         */
        Board *getBoard();

        /**
         * @return True, pokud byl v minulém úspěšném tahu šach. Relevantní pouze po úspěšném volání move(). Pouze šachy
         */
        bool getCheck();

        /**
         * @return True, pokud byla v minulém úspěšném tahu vyhozena figurka. Relevantní pouze po úspěšném volání move(). Pouze šachy
         */
        bool byloVyhozeni();

        /**
         * @return Vrací vektor figurek této hry.
         */
        std::vector<std::shared_ptr<Figure>> *getFigures();

        /**
         * @return Vrací zásobník provedených tahů
         */
        std::deque<Tah> *getMoves();

        /**
         * @return Vrací zásobník vrácených retahů
         */
        std::deque<Tah> *getRedoMoves();

        /**
         * @param to Nastaví, na co se bude pěšec povyšovat.
         */
        void setPromoteTo(char to);

        /**
         * @return Vrací na co se bude pěšec povyšovat.
         */
        char getPromoteTo();

        /**
         * @return True, pokud je další hráč na tahu bílý. Pouze checkers
         */
        bool isNextWhite();
    private:

    protected:
        Board *deska;
        bool destroyBoard = false;
        std::deque<Tah> tahy;
        std::deque<Tah> retahy;
        std::vector<std::shared_ptr<Figure>> figures;
        bool check = false;
        bool vyhozeni = false;
        Adapter *adapter;
        int cisloTahu = 1;
        char promoteTo = 'D';
        bool nextMoveWhite = true;
};


#endif
