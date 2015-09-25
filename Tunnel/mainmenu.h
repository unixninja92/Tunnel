/*
 *  Tunnel Copyright 2015 unixninja92
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  @author unixninja92
 */
#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QPushButton>
#include <tunnelw.h>

namespace Ui {
class MainMenu;
}

/*
 *  MainMenu is the main screen that appears when the user starts
 *  Tunnel. It has options for starting a game at each difficulty
 *  and button for navigating to the score boards and settings menu.
 */
class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

protected:

private slots:
    void easyMode();
    void medMode();
    void hardMode();
    void insaneMode();
    void scores();
    void settings();

private:
    Ui::MainMenu *ui;
    TunnelW *tunnel;
    QPushButton *easy;
    QPushButton *med;
    QPushButton *hard;
    QPushButton *insane;
    QPushButton *score;
    QPushButton *setting;

    //starts a game with the given difficulty parameters
    void start(int, double, double);
};

#endif // MAINMENU_H
