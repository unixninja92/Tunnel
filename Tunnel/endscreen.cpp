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

EndScreen::EndScreen(share s, TunnelW* t, Level l, QWidget *parent) :
    QWidget(parent)
{
    shared = s;
    tun = t;
    level = l;
    endBox = new QMessageBox(tun->menu);
    endBox->setText("Score: ");
    menuButton = endBox->addButton("Main menu",QMessageBox::NoRole);
    againButton = endBox->addButton("Play again", QMessageBox::AcceptRole);

}

void EndScreen::exec()
{
    int scoreI = tun->getScore();
//    std::stringstream ss;
//    ss << scoreI;
//    std::string s = ss.str();
//    const char *c = s.c_str();
    QString score = QString::number(scoreI);//(c);
    QString text;
    QString high = settings.value("score/"+QString::number(level)+"/0").toString();
    if(scoreI > settings.value("score/"+QString::number(level)+"/0").toInt()) {
        text = "Congratulations!!! New High Score!\n" + endBox->text() + score +
                "\nPrevious High Score:" + high;
        settings.setValue("score/"+QString::number(level)+"/"+QString::number(0), score);
    }
    else{
        text = "High Score: " + high + "\n" + endBox->text() + score;
    }
    endBox->setText(text);
    endBox->exec();
    if(endBox->clickedButton() == againButton){
        tun->restartGame();
    }
    else if(endBox->clickedButton() == menuButton){
        tun->hide();
        tun->menu->show();
        tun->menu->newTunnel();
    }
}

