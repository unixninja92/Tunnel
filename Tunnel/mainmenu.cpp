/*
 * Tunnel Copyright 2015 unixninja92
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
 */
#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "tunnel.h"
#include "tunnelwindow.h"

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    easy = ui->easyButton;
    med = ui->mediumButton;
    hard = ui->hardButton;
    insane = ui->insaneButton;
    score = ui->scoreButton;
    setting = ui->settingsButton;

    connect(easy, SIGNAL(released()), this, SLOT(easyMode()));
    connect(med, SIGNAL(released()), this, SLOT(medMode()));
    connect(hard, SIGNAL(released()), this, SLOT(hardMode()));
    connect(insane, SIGNAL(released()), this, SLOT(insaneMode()));
    connect(score, SIGNAL(released()), this, SLOT(scores()));
    connect(setting, SIGNAL(released()), this, SLOT(settings()));

    tunnelWindow = new TunnelWindow();
    tunnel = tunnelWindow->tunnel;
    tunnel->menu = this;
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::easyMode()
{
    start(100, 1, 1, Easy);
}

void MainMenu::medMode()
{
    start(100, 2, 3, Medium);
}

void MainMenu::hardMode()
{
    start(96, 5, 4, Hard);
}

void MainMenu::insaneMode()
{
    start(113, 7.5, 5, Insane);
}

/*
 * pHeight is the heght of each wall block
 * pMove is how many pixles the polygonBlocks move each frame
 * dMove is how many pixles the dot moves each frame
 */
void MainMenu::start(int pHeight, double pMove, double dMove, Level l)
{
    tunnelWindow->show();
    tunnel->show();
    this->hide();
    tunnel->setPHeight(pHeight);
    tunnel->setPMove(pMove);
    tunnel->setDMove(dMove);
    if(!tunnel->hasStarted())
        tunnel->runGame(l);
    else
        tunnel->restartGame();
}

void MainMenu::newTunnel()
{
    delete tunnelWindow;
    tunnelWindow = new TunnelWindow();
    tunnel = tunnelWindow->tunnel;
    tunnel->menu = this;
}

void MainMenu::settings()
{

}

void MainMenu::scores()
{

}
