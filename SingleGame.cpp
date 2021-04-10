//
// Created by Yongpu Jia on 2020/4/14.
//

#include "SingleGame.h"
#include "Step.h"
#include <QTimer>

SingleGame::SingleGame(bool red) : Board(red) {
    level = 5;
}

void SingleGame::click(int id, int row, int col) {
    if (redturn) {
        Board::click(id, row, col);
        if (!redturn) {
            QTimer::singleShot(100, this, SLOT(computerMove()));
        }
    }
}

void SingleGame::computerMove() {
    Step *step = think();
    moveStone(step->moveid, step->rowto, step->colto, step->killid);
    delete step;
    update();
}

Step *SingleGame::think() {
    QVector<Step *> steps = getAllPossibleStep();
    int maxscore = -1000000;
    Step *beststep = NULL;
    while (steps.count()) {
        Step *step = steps.back();
        steps.removeLast();
        fakeMove(step);
        int score = getMinScore(level - 1, maxscore);
        unFakeMove(step);
        if (score > maxscore) {
            maxscore = score;
            if (beststep != NULL) delete beststep;
            beststep = step;
        } else {
            delete step;
        }
    }
    return beststep;
}

QVector<Step *> SingleGame::getAllPossibleStep() {
    QVector<Step *> steps;
    int min, max;
    if (redturn) {
        min = 16;
        max = 32;
    } else {
        min = 0;
        max = 16;
    }
    for (int i = min; i < max; i++) {
        if (s[i].dead) continue;
        for (int row = 1; row <= 10; row++) {
            for (int col = 1; col <= 9; col++) {
                int killid = getStoneId(row, col);
                if (canMove(i, row, col, killid)) {
                    saveStep(i, row, col, killid, steps);
                }
            }
        }
    }
    return steps;
}


void SingleGame::fakeMove(Step *step) {
    if (step->killid != -1) s[step->killid].dead = true;
    moveStone(step->moveid, step->rowto, step->colto);
}

//enum TYPE{JIANG,CHE,PAO,MA,BING,SHI,XIANG};
int SingleGame::calcScore() {
    static int chessScore[] = {1000, 10, 5, 4, 1, 2, 2};
    int blacktotal = 0;
    int redtotal = 0;
    for (int i = 0; i < 16; i++) {
        if (!s[i].dead) {
            blacktotal += chessScore[s[i].type];
        }
    }
    for (int i = 16; i < 32; i++) {
        if (!s[i].dead) {
            redtotal += chessScore[s[i].type];
        }
    }
    return blacktotal - redtotal;
}

void SingleGame::unFakeMove(Step *step) {
    if (step->killid != -1) s[step->killid].dead = false;
    moveStone(step->moveid, step->rowfrom, step->colfrom);
}

int SingleGame::getMinScore(int level, int curmaxscore) {
    if (level == 0) return calcScore();
    QVector<Step *> steps = getAllPossibleStep();
    int minscore = 1000000;
    while (steps.count()) {
        Step *step = steps.back();
        steps.removeLast();
        fakeMove(step);
        int score = getMaxScore(level - 1, minscore);
        unFakeMove(step);
        delete step;
        if (score <= curmaxscore) {
            while (steps.count()) {
                step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }
        if (score < minscore) {
            minscore = score;
        }
    }
    return minscore;
}

int SingleGame::getMaxScore(int level, int curminscore) {
    if (level == 0) return calcScore();
    QVector<Step *> steps = getAllPossibleStep();
    int maxscore = -1000000;
    while (steps.count()) {
        Step *step = steps.back();
        steps.removeLast();
        fakeMove(step);
        int score = getMinScore(level - 1, maxscore);
        unFakeMove(step);
        delete step;
        if (score >= curminscore) {
            while (steps.count()) {
                step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }
        if (score > maxscore) {
            maxscore = score;
        }
    }
    return maxscore;
}

void SingleGame::slotBack() {
    if (redturn) {
        backOne();
        backOne();
    }
}

