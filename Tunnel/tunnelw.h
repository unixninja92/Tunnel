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
#ifndef TUNNELW_H
#define TUNNELW_H

#include <shared.h>
//#include <dot.h>
#include <mainmenu.h>
#include <movingpolygons.h>
#include <score.h>
#include <endscreen.h>

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
    void timerEvent(QTimerEvent *);

private:
    Ui::TunnelW *ui;
    void createScene(int w, int h);
    share shared;
    bool started;
    int dSpeed;
    int pSpeed;
    double dMove;
    double pMove;
    bool moveLeft;
    bool moveRight;
    int frameTimer;
};

#endif // TUNNELW_H
