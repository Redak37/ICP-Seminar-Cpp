/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

using namespace std;

/**
 * @brief The Message class - zpráva pro předání pozive stisknutého tlačítka
 */
class Message
{
public:
    /**
     * @brief Message
     * @param r
     * @param s
     */
    Message(int r = -1, int s = -1);
    ~Message();

    int radek;
    int sloupec;

};

#endif // MESSAGE_H
