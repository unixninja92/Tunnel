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
#ifndef DOT_H
#define DOT_H

#include <QObject>
#include <QWidget>
#include <shared.h>
#include <movingpolygons.h>
#include <score.h>
#include <endscreen.h>

class Dot : public QWidget
{
    Q_OBJECT
public:
    explicit Dot(share, QWidget *parent = 0);

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);

private:
    share shared;
    QGraphicsEllipseItem* dot;
    bool left;
    bool right;
    int timer;
};

//class Dot : public QWidget
//{
//    Q_OBJECT
//public:
//    explicit Dot(QWidget *parent = 0);
//    ~Dot();

//signals:

//public slots:
//};

#endif // DOT_H
