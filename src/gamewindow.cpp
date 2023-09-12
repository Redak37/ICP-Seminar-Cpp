/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include "gamewindow.hpp"
#include "ui_gamewindow.h"

#include <QAbstractButton>
#include <QPushButton>
#include <QDebug>
#include <QStringListModel>
#include <QStringList>

#include <QFileDialog>

#include <string>
#include <cstdio>
#include <fstream>

#include "Board.hpp"
#include "Game.hpp"
#include "games/ChessGame.hpp"
#include "games/CheckersGame.hpp"

GameWindow::GameWindow(QWidget *parent, bool sachy) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    QObject::connect(this, SIGNAL(messageSent(Message)), this, SLOT(setMessage(Message)));

    this->initPolicka();
    this->sachy = sachy;

    //Game
    adapter = new Adapter(this);
    if(sachy){
        adapter->registerGame( (Game*) new ChessGame(nullptr, adapter) );
    } else {
        adapter->registerGame( (Game*) new CheckersGame(nullptr, adapter) );
        this->ui->comboBox_promote->hide();
        this->ui->label->hide();
    }


    this->ui->spinBox_auto->setRange(0.2, 10);
    this->ui->spinBox_auto->setSingleStep(0.2);
    this->ui->spinBox_auto->setValue(1);
    //parser = new Parser(adapter->getGame());
    //////////////////////////

    //this->ui->listView->
    move_model = new QStringListModel(this->ui->listView);
    move_list = new QStringList();
    *move_list << "1.";
    move_model->setStringList(*move_list);
    this->ui->listView->setModel(move_model);
    QModelIndex Index= ui->listView->model()->index(0,0);
    this->ui->listView->selectionModel()->select( Index, QItemSelectionModel::Select );
}

GameWindow::~GameWindow()
{
    delete adapter;
    delete ui;
}



void GameWindow::initPolicka(){
    for(int radky = 0; radky < 8; ++radky){
        for(int sloupce = 0; sloupce < 8; ++sloupce){
            QSize velikost_ikony = QSize(55,55);
            QString nazev = QString(("butt_r" + std::to_string(radky) + "_s" + std::to_string(sloupce)).c_str());

            QPushButton *butt = new QPushButton(this->ui->frame);
            policka[radky][sloupce] = butt;
            butt->resize(60,60);
            butt->move(60 * sloupce, 60 * radky);
            butt->setIconSize(velikost_ikony);

            butt->setObjectName(nazev);
            this->setFieldColor(radky, sloupce, false);

            connect(butt, SIGNAL(pressed()), this, SLOT(sendMessage()));

            //qDebug("policko r%d s%d\n", radky, sloupce);
        }
    }
}



void GameWindow::sendMessage()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
     if (pButton) {
         QPoint p = pButton->pos();
         thisMessage = Message(7 - p.y()/60, p.x()/60);
         emit messageSent(thisMessage);
     }
}

void GameWindow::setMessage(const Message &message)
{
    thisMessage = message;
    //qDebug("Klik r%d s%d\n", thisMessage.radek, thisMessage.sloupec);

    if(aktivni){
        aktivni = false;
        if(adapter->figMove(aktivni_r, aktivni_s, thisMessage.radek, thisMessage.sloupec)){
            if(sachy){
                posledni_tah_bila = !posledni_tah_bila;
                loadMovesChess();
            } else {
                posledni_tah_bila = !adapter->getGame()->isNextWhite();
                loadMovesCheckers();
            }
        }
    }

    int is_fig = adapter->isFigure(thisMessage.radek, thisMessage.sloupec);
    bool barva_bila = is_fig - 1;

    if(is_fig && barva_bila != posledni_tah_bila) {
        aktivni_r = thisMessage.radek;
        aktivni_s = thisMessage.sloupec;
        aktivni = true;
        this->setFieldColor(7 - thisMessage.radek, thisMessage.sloupec, true);
    } else {
        this->setFieldColor(7 - thisMessage.radek, thisMessage.sloupec, false);
    }
}


void GameWindow::setFieldColor(int radek, int slopec, bool aktivni){
    if(((l_radek + l_sloupec) & 1) == 0)
        policka[l_radek][l_sloupec]->setStyleSheet(StylBile_Neaktivni);
    else
        policka[l_radek][l_sloupec]->setStyleSheet(StylCerne_Neaktivni);

    l_sloupec = slopec;
    l_radek = radek;

    if(((radek + slopec) & 1) == 0){
        if(aktivni){
            policka[radek][slopec]->setStyleSheet(StylBile_Aktivni);
        } else {
            policka[radek][slopec]->setStyleSheet(StylBile_Neaktivni);
        }
    } else {
        if(aktivni){
            policka[radek][slopec]->setStyleSheet(StylCerne_Aktivni);
        } else {
            policka[radek][slopec]->setStyleSheet(StylCerne_Neaktivni);
        }
    }
}


void GameWindow::drawFig(int radek, int sloupec, const char *obrazek){
    if(obrazek)
        policka[radek][sloupec]->setIcon(QIcon(obrazek));
    else
        policka[radek][sloupec]->setIcon(QIcon());
}



void GameWindow::on_button_sachy_clicked()
{
    QTabWidget *tab = (QTabWidget *) this->parent()->parent();
    tab->addTab(new GameWindow(tab, true), QString("Šachy"));
}

void GameWindow::on_button_dama_clicked()
{
    QTabWidget *tab = (QTabWidget *) this->parent()->parent();
    tab->addTab(new GameWindow(tab, false), QString("Dáma"));
}


void GameWindow::on_button_vpred_clicked()
{
    if(adapter->getGame()->getRedoMoves()->empty())
       return;
    Tah move = adapter->getGame()->getRedoMoves()->front();
    if(adapter->redo()){
        //posunChess(1, move);
    }
    posledni_tah_bila = !posledni_tah_bila;
    ui->listView->clearSelection();
}

void GameWindow::on_button_zpet_clicked()
{
    if(adapter->getGame()->getMoves()->empty())
       return;
    Tah move = adapter->getGame()->getMoves()->front();
    if(adapter->undo()){
        //posunChess(-1, move);
    }
    posledni_tah_bila = !posledni_tah_bila;
    ui->listView->clearSelection();
}

void GameWindow::on_comboBox_promote_currentIndexChanged(const QString &arg1)
{
    adapter->promoteTo(arg1.toStdString().c_str()[0]);
}

void GameWindow::on_button_auto_clicked()
{
    if(auto_play){
        auto_play = false;
        adapter->autoPlay(false);
        this->ui->button_zpet->show();
        this->ui->button_vpred->show();
        this->ui->button_auto->setStyleSheet("color: white; background-color: red");
    } else {
        auto_play = true;
        adapter->autoPlay(true);
        this->ui->button_zpet->hide();
        this->ui->button_vpred->hide();
        this->ui->button_auto->setStyleSheet("color: red; background-color: white");
    }
    ui->listView->clearSelection();
}


void GameWindow::redo_s(void){
    if(!adapter->redo())
        this->on_button_auto_clicked();
}

void GameWindow::on_spinBox_auto_valueChanged(double arg1)
{
    if(adapter)
        adapter->setTimer(arg1);
}

void GameWindow::on_listView_clicked(const QModelIndex &index)
{
    //qDebug("polozka %d\n", index.row());
    while(adapter->undo());
    for(int i = 0; i < index.row(); ++i){
        adapter->redo();
        if(sachy)
            adapter->redo();
    }
    posledni_tah_bila = false;
}

void GameWindow::on_button_nacti_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
           tr("Načíst hru"), "",
           tr("Záznam šachu (*.txt);;All Files (*)"));
    //qDebug() << fileName << endl;
    if(fileName == "")
        return;

    int kolik = 1;
    if(sachy){
        adapter->registerGame( (Game*) new ChessGame(NULL, adapter) );
    } else {
        adapter->registerGame( (Game*) new CheckersGame(NULL, adapter) );
    }
    parser = new Parser(adapter->getGame());
    parser->read(fileName.toStdString());

    move_list->clear();
    for(string k : parser->getMoves()){
        ++kolik;
        move_list->append(*(new QString(k.c_str())));
    }
    if(move_list->back().split(" ").length() == 3)
        move_list->append(QString((to_string(kolik) + ".").c_str()));
    //move_list.getSelectionModel().select(0);
    //userSelected = true;

    this->ui->listView->update();
    move_model->setStringList(*move_list);
    this->ui->listView->setModel(move_model);

    QModelIndex Index= ui->listView->model()->index(0,0);
    this->ui->listView->selectionModel()->select( Index, QItemSelectionModel::Select );
}

void GameWindow::on_button_uloz_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Uložit hru"), "",
            tr("Záznam šachu (*.txt);;All Files (*)"));
    //qDebug() << fileName << endl;
    if(fileName != ""){
        ofstream vystup(fileName.toStdString());
        for(QString radek : *move_list){
            if(radek.split(" ").length() > 1)
                vystup << radek.toStdString() << endl;
        }
        vystup.flush();
        vystup.close();
    }

}



void GameWindow::loadMovesChess(){
    int kolik = 1;
    move_list->clear();
    string move = "";
    for(auto a = adapter->getGame()->getMoves()->rbegin(); a != adapter->getGame()->getMoves()->rend(); ++a ){
        if(move == ""){
              move += a->getState();
          }
          else{
              move += a->getState();
              *move_list << move.c_str();
              move = "";
              ++kolik;
          }
    }
    if(move != ""){
        *move_list << move.c_str();
    }
    else{
         move_list->append(QString((to_string(kolik) + ".").c_str()));

    }

    this->ui->listView->update();
    move_model->setStringList(*move_list);
    this->ui->listView->setModel(move_model);
    QModelIndex Index= ui->listView->model()->index(kolik - 1, 0);
    this->ui->listView->selectionModel()->select( Index, QItemSelectionModel::Select );
}
void GameWindow::loadMovesCheckers()
{
    int kolik = 1;
    move_list->clear();
    string move = "";
    bool bylNaTahuBily = true;
    for(auto tah = adapter->getGame()->getMoves()->rbegin(); tah != adapter->getGame()->getMoves()->rend(); ++tah ){
        if(move == ""){
            move += to_string(kolik) + ". ";
            move += tah->getState();
            bylNaTahuBily = tah->figurka()->isWhite();
        }
        else{
            if(tah->figurka()->isWhite() == bylNaTahuBily){
                move += " " + tah->getState();
            }
            else{
                *move_list << move.c_str();
                kolik++;
                move = "";
                move += to_string(kolik) + ". ";
                move += tah->getState();
                bylNaTahuBily = tah->figurka()->isWhite();
            }
                            }
    }
    if(move != ""){
        *move_list << move.c_str();
    }
    else{
         move_list->append(QString((to_string(kolik) + ".").c_str()));
    }

    this->ui->listView->update();
    move_model->setStringList(*move_list);
    this->ui->listView->setModel(move_model);
    QModelIndex Index= ui->listView->model()->index(kolik - 1, 0);
    this->ui->listView->selectionModel()->select( Index, QItemSelectionModel::Select );
}
