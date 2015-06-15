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
#ifndef DOT_H
#define DOT_H

#include <QObject>
#include <QOpenGLWidget>
#include <shared.h>
#include <movingpolygons.h>
#include <score.h>
#include <endscreen.h>

#define DOT_DIAMETER TUNNEL_WIDTH/5

/*
 *  Dot creates and moves the ship that the user is controlling
 *  back and forth on screen based on keyboard events.
 */
class Dot : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit Dot(share, int, double, QOpenGLWidget *parent = 0);

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);

private:
    share shared;
    QGraphicsEllipseItem* dot;
    bool moveLeft;
    bool moveRight;
    int timer;
    double pixlesToMove;
};

#endif // DOT_H
