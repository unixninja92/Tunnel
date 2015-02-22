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
#ifndef SCORE_H
#define SCORE_H

#include <QObject>
#include <shared.h>

class Score : public QObject
{
    Q_OBJECT
public:
    explicit Score(share, QObject *parent=0);
    void killTime();
    void updateScore();
    int getScore();

protected:
    void timerEvent(QTimerEvent *event);

private:
    share shared;
    QGraphicsSimpleTextItem* scoreKeeper;
    int score;
    int scoreTimer;
};

#endif // SCORE_H
