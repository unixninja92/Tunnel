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
