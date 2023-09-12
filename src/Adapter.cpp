/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include "Adapter.hpp"
#include "Game.hpp"
#include "gamewindow.hpp"
#include <QObject>

static const char *figurky[24]{
    "data/image/BD.png",
    "data/image/BJ.png",
    "data/image/BK.png",
    "data/image/Bp.png",
    "data/image/BS.png",
    "data/image/BV.png",

    "data/image/WD.png",
    "data/image/WJ.png",
    "data/image/WK.png",
    "data/image/Wp.png",
    "data/image/WS.png",
    "data/image/WV.png",

    "data/image2/dama_c.png",
    "data/image2/jezdec_c.png",
    "data/image2/kral_c.png",
    "data/image2/pesec_c.png",
    "data/image2/strelec_c.png",
    "data/image2/vez_c.png",

    "data/image2/dama_b.png",
    "data/image2/jezdec_b.png",
    "data/image2/kral_b.png",
    "data/image2/pesec_b.png",
    "data/image2/strelec_b.png",
    "data/image2/vez_b.png"
};



Adapter::Adapter(GameWindow *gui_p, Game *hra_p)
{
    gui = gui_p;
    hra = hra_p;

    timer.setTimerType(Qt::CoarseTimer);
    timer.setInterval(1000);
    QObject::connect(&timer, SIGNAL(timeout()), gui, SLOT(redo_s()));
}

Adapter::~Adapter()
{
    delete hra;
}

int Adapter::isFigure(int radek, int sloupec){
    Field *f = hra->getBoard()->getField_normal(sloupec, radek);
    if(f->isEmpty())
        return 0;
    if(f->get()->isWhite())
        return 2;
    else
        return 1;
}

bool Adapter::figMove(int odkud_r, int odkud_s, int kam_r, int kam_s){
    Field *odkud = hra->getBoard()->getField_normal(odkud_s, odkud_r);
    Field *kam = hra->getBoard()->getField_normal(kam_s, kam_r);
    Figure *fig = odkud->get();
    if(!fig)
        return false;
    return hra->move(fig, kam,true);
}

void Adapter::draw(int radek, int sloupec, bool bila, char znakFigurky){
    int fig = 40;
    switch (znakFigurky) {
        case 'D': fig = 0; break;
        case 'J': fig = 1; break;
        case 'K': fig = 2; break;
        case 'p': fig = 3; break;
        case 'S': fig = 4; break;
        case 'V': fig = 5; break;
        case ' ': {
            gui->drawFig(7 - radek, sloupec, NULL);
            return;
        }
    }
    fig += bila * 6;
    //fig += 12;
    if(fig >= 40)
        return;
    gui->drawFig(7 - radek, sloupec, figurky[fig]);
}


bool Adapter::redo(void){
    return hra->redo();
}

bool Adapter::undo(void){
    return hra->undo();
}


void Adapter::registerGame(Game *hra_p){
    hra = hra_p;
}

void Adapter::autoPlay(bool start){
    if(start)
        timer.start();
    else
        timer.stop();
}

void Adapter::promoteTo(char x){
    hra->setPromoteTo(x);
}

void Adapter::setTimer(double x){
    timer.setInterval((int) (x * 1000));
}

Game *Adapter::getGame(){
    return hra;
}
