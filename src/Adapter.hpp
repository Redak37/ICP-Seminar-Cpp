/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef Adapter_HPP
#define Adapter_HPP

#include <QObject>
#include <cstdbool>
#include <QTimer>

class GameWindow;
class Game;


/**
 * @brief Třída která slouží k propojení backendu hry a gui
 */
class Adapter {

    public:
        /**
         * @brief Adapter
         * @param gui_p ukazetel na třídu GameWindow (gui)
         * @param hra_p je ukazatel na třídu Game (backend)
         */
        explicit Adapter(GameWindow *gui_p, Game *hra_p = NULL);
        ~Adapter();

        /**
         * @brief registerGame propojí adaptér s Game
         * @param hra_p je ukazatel na třídu Game (backend)
         */
        void registerGame(Game *hra_p);
        /**
         * @brief isFigure zjistí jestli jaká je na pozici figurka
         * @param radek
         * @param sloupec
         * @return 0 - žádná; 1 - černá; 2 - bílá
         */
        int isFigure(int radek, int sloupec);
        /**
         * @brief figMove pohne s figurkou z pozice na pozici
         * @param odkud_r řádek
         * @param odkud_s sloupec
         * @param kam_r řádek
         * @param kam_s sloupec
         * @return true - pohyb se povedl; false - pohyb se nepovedl
         */
        bool figMove(int odkud_r, int odkud_s, int kam_r, int kam_s);
        /**
         * @brief draw vykreslí v gui figurku
         * @param radek
         * @param sloupec
         * @param bila (jestli je figurka bílá)
         * @param znakFigurky
         */
        void draw(int radek, int sloupec, bool bila, char znakFigurky);
        /**
         * @brief redo, tah vpřed
         * @return jestli se redo povedlo
         */
        bool redo(void);
        /**
         * @brief undo, tah vzad
         * @return jestli se unndo povedlo
         */
        bool undo(void);
        /**
         * @brief autoPlay zastavuje nebo spouští přehrávání
         * @param start (true), stop (false)
         */
        void autoPlay(bool start);
        /**
         * @brief promoteTo povýšit na
         * @param x znak figurky
         */
        void promoteTo(char x);
        /**
         * @brief setTimer nastaví timer autopřehrávání
         * @param x
         */
        void setTimer(double x);
        /**
         * @brief getGame
         * @return *Game
         */
        Game *getGame();

    private:
        Game *hra = NULL;
        GameWindow *gui = NULL;
        QTimer timer;
};

#endif // Adapter_HPP
