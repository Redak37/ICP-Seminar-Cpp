/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include <QWidget>

#include <QAbstractButton>
#include <QString>
#include <cstdbool>

#include "Message.hpp"
#include "Adapter.hpp"
#include "Parser.hpp"
#include "Tah.hpp"

#include <QStringListModel>

const QString StylBile_Neaktivni = "background-color: rgb(255, 255, 255);\
                                    color: black;\
                                    border-style: solid;\
                                    border-width: 1px;\
                                    border-color: rgb(150, 150, 150);\
                                    min-width: 40px;\
                                    min-height: 40px;";

const QString StylCerne_Neaktivni = "background-color: rgb(0, 0, 0);\
                                    color: black;\
                                    border-style: solid;\
                                    border-width: 1px;\
                                    border-color: rgb(150, 150, 150);\
                                    min-width: 40px;\
                                    min-height: 40px;";

const QString StylBile_Aktivni = "background-color: rgb(255, 125, 125);\
                                    color: black;\
                                    border-style: solid;\
                                    border-width: 1px;\
                                    border-color: red;\
                                    min-width: 40px;\
                                    min-height: 40px;";

const QString StylCerne_Aktivni = "background-color: rgb(100, 0, 0);\
                                    color: black;\
                                    border-style: solid;\
                                    border-width: 1px;\
                                    border-color: red;\
                                    min-width: 40px;\
                                    min-height: 40px;";

namespace Ui {
class GameWindow;
}

/**
 * @brief The GameWindow class - gui hrací plochy
 */
class GameWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief GameWindow
     * @param parent
     * @param sachy (true) / dama (false)
     */
    explicit GameWindow(QWidget *parent = nullptr, bool sachy = true);
    ~GameWindow();
    /**
     * @brief drawFig vykreslí obrázek do políčka na pozici
     * @param radek
     * @param sloupec
     * @param obrazek string s cestou k obrázku
     */
    void drawFig(int radek, int sloupec, const char *obrazek);


signals:
    void messageSent(const Message &message);

public slots:
    /**
     * @brief setMessage obsluhuje přijatou zprávu
     * @param message
     */
    void setMessage(const Message &message);
    /**
     * @brief redo_s obsluhuje volání timeru
     */
    void redo_s();

private slots:
    void sendMessage();

    void on_button_sachy_clicked();

    void on_button_dama_clicked();

    void on_button_vpred_clicked();

    void on_button_zpet_clicked();

    void on_comboBox_promote_currentIndexChanged(const QString &arg1);

    void on_button_auto_clicked();

    void on_spinBox_auto_valueChanged(double arg1);

    void on_listView_clicked(const QModelIndex &index);

    void on_button_nacti_clicked();

    void on_button_uloz_clicked();

private:
    Ui::GameWindow *ui;

    QAbstractButton *policka[9][9] = {{nullptr}};
    Message thisMessage;
    Adapter *adapter;

    bool aktivni = false;
    bool posledni_tah_bila = false;
    int aktivni_r = -1;
    int aktivni_s = -1;

    int l_radek = 0;
    int l_sloupec = 0;

    bool auto_play = false;

    void initPolicka();
    void setFieldColor(int radek, int slopec, bool aktivni);

    Parser *parser;
    QStringList *move_list;
    QStringListModel *move_model;

    bool sachy;

    void loadMovesChess();
    void loadMovesCheckers();

};

#endif // GAMEWINDOW_HPP
