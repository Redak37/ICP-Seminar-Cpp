/**
 * ICP 2018/2019
 * Projekt - Šachy/Dáma
 *
 * @author Radek Duchoň (xducho07)
 * @author Jan Juda (xjudaj00)
 * @author Josef Oškera (xosker03)
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * @param parent
     */
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void closeTab(int t);

    void on_button_sachy_main_clicked();

    void on_button_dama_main_clicked();

private:
    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
};

#endif // MAINWINDOW_H
