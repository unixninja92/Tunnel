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
#include "endscreen.h"
#include "mainmenu.h"
#include <sstream>

EndScreen::EndScreen(share s, TunnelW* t, QWidget *parent) :
    QWidget(parent)
{
    shared = s;
    tun = t;
    endBox = new QMessageBox(tun->menu);
    endBox->setText("Score ");
    menuButton = endBox->addButton("Main menu",QMessageBox::DestructiveRole);
    againButton = endBox->addButton("Play again", QMessageBox::ResetRole);
}

void EndScreen::exec()
{
    int scoreI = tun->getScore();
    std::stringstream ss;
    ss << scoreI;
    std::string s = ss.str();
    const char *c = s.c_str();
    QString score(c);
    QString text = "Score: " + score;
    endBox->setText(text);
    endBox->exec();
    if(endBox->clickedButton() == againButton){
        tun->restartGame();
    }
    else if(endBox->clickedButton() == menuButton){
        tun->hide();
        tun->menu->show();
    }
}

