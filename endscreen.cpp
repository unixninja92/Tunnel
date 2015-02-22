/*
 *Copyright 2014 unixninja92
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
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
    menu = endBox->addButton("Main menu",QMessageBox::DestructiveRole);
    again = endBox->addButton("Play again", QMessageBox::ResetRole);
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
    if(endBox->clickedButton() == again){
        tun->restartGame();
    }
    else if(endBox->clickedButton() == menu){
        tun->hide();
        tun->menu->show();
    }
}

