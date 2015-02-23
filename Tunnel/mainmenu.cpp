/*
 *Copyright 2015 unixninja92
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
#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "tunnelw.h"

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


    tunnel = new TunnelW();
    tunnel->menu = this;
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::easyMode()
{
    start(40);
}

void MainMenu::medMode()
{
    start(20);
}

void MainMenu::hardMode()
{
    start(10);
}

void MainMenu::insaneMode()
{
    start(2);
}

void MainMenu::start(int speed)
{
    tunnel->show();
    this->hide();
    tunnel->setSpeed(speed);
    if(!tunnel->hasStarted())
        tunnel->startGame();
    else
        tunnel->restartGame();
}

void MainMenu::settings()
{

}

void MainMenu::scores()
{

}
