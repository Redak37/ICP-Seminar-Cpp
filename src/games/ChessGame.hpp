#ifndef CHESSGAME_HPP
#define CHESSGAME_HPP

#include "../Board.hpp"
#include "../Game.hpp"
#include "Adapter.hpp"

/**
 * @brief Třída pro hru v šachu
 */
class ChessGame: public Game {
    public:
        /**
         * @brief Vytvoří hru šachů a rozestaví na desku figurky.
         * @param board
         */
        ChessGame(Board *board = nullptr, Adapter *adapter_p = nullptr);
        virtual ~ChessGame();

        /**
         * @brief Provede pohyb s figurkou na políčko.
         * @param figure - hýbaná figurka
         * @param field - cílové políčko
         * @param userMove - true, pokud se jedná o tah, který provedl uživatel. V tomto případě se vyprázdní vektor retahů pro redo()
         * @return true, pokud byl pohyb úspěšný
         */
        bool move(Figure *figure, Field *field, bool userMove);

        /**
         * @brief Vrátí předchozí tah.
         * @return True, pokud se undo provedlo (zásobník tahů nebyl prázdný)
         */
        bool undo();

        /**
         * @brief Znovu provede vrácený tah.
         * @return True, pokud se redo provedlo (zásobník retahů nebyl prázdný)
         */
        bool redo();

    private:
        std::string generateState(Figure *figure, Field *from, Field *to, bool vyhozeni, char povyseni);
};

#endif // CHESSGAME_HPP
