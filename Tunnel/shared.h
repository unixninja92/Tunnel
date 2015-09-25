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
#ifndef SHARED
#define SHARED

#define TUNNEL_WIDTH 100
#define DOT_DIAMETER (TUNNEL_WIDTH/5)
#define WIDTH_MODIFIER (TUNNEL_WIDTH/2)
#define FRAMES_PER_SECOND 100

#include <QWidget>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QPointer>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsEllipseItem>

class MovingPolygons;
class Score;
class EndScreen;
class TunnelW;

typedef struct Share{
    QPointer<QGraphicsScene> scene;
    int pHeight;
    static bool isPaused;
}share;

namespace Ui {
class TunnelW;
}

#endif // SHARED

