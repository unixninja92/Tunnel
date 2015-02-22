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
#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QPushButton>
#include <tunnelw.h>

namespace Ui {
class MainMenu;
}

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
    void start(int);
};

#endif // MAINMENU_H
