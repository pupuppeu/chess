//
// Created by Yongpu Jia on 2020/4/14.
//

#ifndef CHESS_SINGLEGAME_H
#define CHESS_SINGLEGAME_H


#include "Board.h"
#include "Step.h"

class SingleGame : public Board {
Q_OBJECT
public:
    SingleGame(bool redside);

    void click(int id, int row, int col);

    Step *think();

    QVector<Step *> getAllPossibleStep();


    void fakeMove(Step *step);

    int calcScore();

    void unFakeMove(Step *step);

    int level;

    int getMinScore(int level, int curmaxscore);

    int getMaxScore(int level, int curminscore);

public slots:

    void computerMove();

    void slotBack();
};


#endif //CHESS_SINGLEGAME_H
