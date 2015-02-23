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
#include "score.h"
#include <sstream>
Score::Score(share s, QObject *parent) :
    QObject(parent)
{
    shared = s;
    score = 0;
    scoreKeeper = shared.scene->addSimpleText(" ");
    scoreKeeper->setPos(shared.scene->width()-30, 20);
    scoreKeeper->setBrush(Qt::white);
    scoreKeeper->setZValue(1);
    updateScore();
    scoreTimer = startTimer(1000);
}

void Score::updateScore()
{
    std::stringstream out;
    out << score;
    scoreKeeper->setText(QString::fromStdString(out.str()));
}

void Score::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==scoreTimer){
        score++;
        updateScore();
    }
}

void Score::killTime()
{
    killTimer(scoreTimer);
}

int Score::getScore()
{
    return score;
}

