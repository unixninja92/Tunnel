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

