/*
 *Copyright 2013 unixninja92
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
#ifndef TUNNELW_H
#define TUNNELW_H

#include <shared.h>
#include <dot.h>
#include <mainmenu.h>

class MainMenu;

class TunnelW : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit TunnelW(QOpenGLWidget *parent = 0);
    ~TunnelW();
    void startGame();
    void restartGame();
    void cleanShared();
    int getScore();
    MainMenu *menu;
    bool hasStarted();
    void setPSpeed(int);
    int getPSpeed();
    void setDSpeed(int);
    int getDSpeed();
    void setDMove(double);
    double getDMove();
    void setPMove(double);
    double getPMove();

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

private:
    Ui::TunnelW *ui;
    void createScene(int w, int h);
    share shared;
    bool started;
    int dSpeed;
    int pSpeed;
    double dMove;
    double pMove;
};

#endif // TUNNELW_H