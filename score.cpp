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

