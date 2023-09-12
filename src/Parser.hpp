/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include "Board.hpp"
#include "Figure.hpp"

/**
 * @brief Třída pro načtení hry v šachu
 */
class Parser
{
    private:
        Figure *figurka;
        Field *pole_do;
        int cislo_tahu = 0;
        Board *deska;
        Game *game;
        std::vector<std::string> tahy;
        bool parse(std::string radek);
    public:

        /**
         * @brief Vytvoří šachový parser na dané hře
         * @param hra - vytvořená hra
         */
        Parser(Game *hra);

        /**
         * @brief Přečte vstupní soubor, zkontrolu notaci zápisu, odsimuluje hru a naplní její vektor retahy pro redo()
         * @param fileName - jméno souboru
         */
        void read(std::string fileName);

        /**
         * @return Vektorů načtených správných tahů. Použitelné pouze po zavolání read()
         */
        std::vector<std::string> getMoves();
};

#endif // PARSER_HPP
