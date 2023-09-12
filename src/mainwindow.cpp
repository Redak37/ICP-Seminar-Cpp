/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * Radek Duchoň (xducho07)
 * Jan Juda (xjudaj00)
 * Josef Oškera (xosker03)
 */
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QTabBar>
#include <QTabWidget>
#include <QString>
#include <QWidget>

#include "gamewindow.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tabWidget = new QTabWidget(this->ui->centralWidget);
    tabWidget->resize(700,580);
    tabWidget->setTabsClosable(true);

    tabWidget->addTab(new GameWindow(tabWidget, true), QString("Šachy"));

    QObject::connect(this->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

}

MainWindow::~MainWindow()
{

}



void MainWindow::closeTab(int t){
    tabWidget->removeTab(t);
    if(tabWidget->count() == 0){
        tabWidget->hide();
    }
}

void MainWindow::on_button_sachy_main_clicked()
{
    tabWidget->addTab(new GameWindow(tabWidget, true), QString("Šachy"));
    tabWidget->show();
}

void MainWindow::on_button_dama_main_clicked()
{
    tabWidget->addTab(new GameWindow(tabWidget, false), QString("Dáma"));
    tabWidget->show();
}
