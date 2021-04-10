//
// Created by Yongpu Jia on 2020/4/13.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <QWidget>
#include "Stone.h"
#include "Step.h"

class Board : public QWidget {
Q_OBJECT
public:
    Board(bool redside);

    Stone s[32];
    int d;
    int selectid;
    bool redturn;
    bool redside;
    QVector<Step *> steps;

    void paintEvent(QPaintEvent *event);

    void drawStone(QPainter &painter, int id);

    void mouseReleaseEvent(QMouseEvent *ev);

    bool canMove(int moveid, int row, int col, int killid);

    int getStoneId(int row, int col);

    bool canMoveJIANG(int moveid, int row, int col, int killid);

    bool canMoveCHE(int moveid, int row, int col, int killid);

    bool canMovePAO(int moveid, int row, int col, int killid);

    bool canMoveMA(int moveid, int row, int col, int killid);

    bool canMoveBING(int moveid, int row, int col, int killid);

    bool canMoveSHI(int moveid, int row, int col, int killid);

    bool canMoveXIANG(int moveid, int row, int col, int killid);

    int getCountStoneAtLine(int row1, int col1, int row2, int col2);

    int getdistance(int id, int row, int col);

    void getClick(QPoint pt, int &row, int &col);

    virtual void click(int id, int row, int col);

    void moveStone(int moveid, int row, int col, int killid);

    void saveStep(int i, int row, int col, int killid, QVector<Step *> &steps);

    void moveStone(int moveid, int row, int col);

    void backOne();

    void drawInitPosition(QPainter &p, int row, int col);

    void drawInitPosition(QPainter &p);

public slots:

    void slotBack();


};


#endif //CHESS_BOARD_H
