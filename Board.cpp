//
// Created by Yongpu Jia on 2020/4/13.
//

#include "Board.h"
#include <QPainter>
#include <QMouseEvent>
#include <algorithm>

using namespace std;

Board::Board(bool red) {
    d = 40;
    setMinimumSize(d * 10, d * 11);
    for (int i = 0; i < 32; i++) {
        s[i].init(i);
    }
    selectid = -1;
    redturn = true;
    redside = red;
    if (!redside) {
        for (int i = 0; i < 32; i++) {
            s[i].col = 10 - s[i].col;
            s[i].row = 11 - s[i].row;
        }
        redside = false;
    }
}

void Board::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    int d = 40;
    for (int i = 1; i <= 10; i++) {
        if (i == 1 || i == 10) {
            painter.setPen(QPen(Qt::black, 2));
        } else {
            painter.setPen(QPen(Qt::black, 1));
        }
        painter.drawLine(d, i * d, 9 * d, i * d);
    }
    for (int i = 1; i <= 9; i++) {
        if (i == 1 || i == 9) {
            painter.setPen(QPen(Qt::black, 2));
            painter.drawLine(d * i, d, d * i, d * 10);
        } else {
            painter.setPen(QPen(Qt::black, 1));
            painter.drawLine(d * i, d, d * i, d * 5);
            painter.drawLine(d * i, d * 6, d * i, d * 10);
        }
    }
    painter.setPen(QPen(Qt::black, 1));
    painter.drawLine(4 * d, d, 6 * d, 3 * d);
    painter.drawLine(QPoint(6 * d, d), QPoint(4 * d, 3 * d));
    painter.drawLine(QPoint(4 * d, 8 * d), QPoint(6 * d, 10 * d));
    painter.drawLine(QPoint(6 * d, 8 * d), QPoint(4 * d, 10 * d));
    drawInitPosition(painter);
    for (int i = 0; i < 32; i++) {
        drawStone(painter, i);
    }

}

void Board::drawStone(QPainter &painter, int id) {
    if (s[id].dead) {
        return;
    }
    QPoint center = s[id].getcenter();
    QRect rect = QRect(center.x() - d / 2, center.y() - d / 2, d, d);
    if (id == selectid) {
        painter.setBrush(QBrush(Qt::gray));
    } else {
        painter.setBrush(QBrush(Qt::yellow));
    }
    if (s[id].red) {
        painter.setPen(QPen(Qt::red, 2));
    } else {
        painter.setPen(QPen(Qt::black, 2));
    }
    painter.drawEllipse(center, d / 2, d / 2);
    painter.setPen(s[id].color);
    painter.setFont(QFont("", 25, 1));
    painter.drawText(rect, s[id].getText(), QTextOption(Qt::AlignCenter));
}

bool Board::canMove(int moveid, int row, int col, int killid) {
    if (killid != -1 && s[moveid].red == s[killid].red) {
        return false;
    }
    switch (s[moveid].type) {
        case Stone::JIANG:
            return canMoveJIANG(moveid, row, col, killid);
        case Stone::CHE:
            return canMoveCHE(moveid, row, col, killid);
        case Stone::BING:
            return canMoveBING(moveid, row, col, killid);
        case Stone::MA:
            return canMoveMA(moveid, row, col, killid);
        case Stone::PAO:
            return canMovePAO(moveid, row, col, killid);
        case Stone::SHI:
            return canMoveSHI(moveid, row, col, killid);
        case Stone::XIANG:
            return canMoveXIANG(moveid, row, col, killid);
    }
    return true;
}

bool Board::canMoveJIANG(int moveid, int row, int col, int killid) {
    if (s[killid].type == Stone::JIANG) {
        return canMoveCHE(moveid, row, col, killid);
    }
    int d = getdistance(moveid, row, col);
    if (d != 10 && d != 1) return false;
    if (col > 6 || col < 4) return false;
    if (s[moveid].red == redside) {
        if (row < 8) return false;
    } else {
        if (row > 3) return false;
    }
    return true;
}

bool Board::canMoveCHE(int moveid, int row, int col, int killid) {
    if (getCountStoneAtLine(s[moveid].row, s[moveid].col, row, col) == 0) {
        return true;
    } else {
        false;
    }
}

bool Board::canMovePAO(int moveid, int row, int col, int killid) {
    int count = getCountStoneAtLine(s[moveid].row, s[moveid].col, row, col);
    if (count != 0 && count != 1) return false;
    if (count == 0) {
        if (killid != -1) return false;
    } else {
        if (killid == -1) return false;
    }
    return true;
}

bool Board::canMoveMA(int moveid, int row, int col, int killid) {
    int d = getdistance(moveid, row, col);
    if (d != 21 && d != 12) return false;
    if (d == 21) {
        if (getStoneId((s[moveid].row + row) / 2, s[moveid].col) == -1) return true;
    } else {
        if (getStoneId(s[moveid].row, (s[moveid].col + col) / 2) == -1) return true;
    }
    return false;
}

bool Board::canMoveBING(int moveid, int row, int col, int killid) {
    int d = getdistance(moveid, row, col);
    if (d != 1 && d != 10) return false;
    if (s[moveid].red == redside) {
        if (s[moveid].row < row) return false;
        if (s[moveid].row > 5 && s[moveid].row == row) return false;
    } else {
        if (s[moveid].row > row) return false;
        if (s[moveid].row < 6 && s[moveid].row == row) return false;
    }
    return true;
}

bool Board::canMoveSHI(int moveid, int row, int col, int killid) {
    if (s[moveid].red == redside) {
        if (row < 8) return false;
    } else {
        if (row > 3) return false;
    }
    if (col > 6 || col < 4) return false;
    int d = getdistance(moveid, row, col);
    if (d == 11) return true;
    else return false;
}

bool Board::canMoveXIANG(int moveid, int row, int col, int killid) {
    int d = getdistance(moveid, row, col);
    if (d != 22) return false;
    if (getStoneId((s[moveid].row + row) / 2, (s[moveid].col + col) / 2) != -1) return false;
    if (s[moveid].red == redside) {
        if (row < 6) return false;
    } else {
        if (row > 5) return false;
    }
    return true;
}


void Board::getClick(QPoint pt, int &row, int &col) {
    if (pt.x() % d < d / 2) col = pt.x() / d;
    else col = pt.x() / d + 1;
    if (pt.y() % d < d / 2) row = pt.y() / d;
    else row = pt.y() / d + 1;
}

void Board::click(int id, int row, int col) {
    if (selectid == -1) {
        if (id != -1 && s[id].red == redturn) {
            selectid = id;
            update();
        }
    } else {
        if (id != -1 && s[selectid].red == s[id].red) {
            selectid = id;
            update();
            return;
        }
        if (canMove(selectid, row, col, id)) {
            moveStone(selectid, row, col, id);
        }
        selectid = -1;
        update();
    }
}

void Board::mouseReleaseEvent(QMouseEvent *ev) {
    QPoint pt = ev->pos();
    int row, col;
    getClick(pt, row, col);
    if (row < 1 || row > 10 || col < 1 || col > 9) return;
    int clickid = getStoneId(row, col);
    click(clickid, row, col);
}

int Board::getStoneId(int row, int col) {
    for (int i = 0; i < 32; i++) {
        if (s[i].row == row && s[i].col == col && !s[i].dead) {
            return i;
        }
    }
    return -1;
}

int Board::getCountStoneAtLine(int row1, int col1, int row2, int col2) {
    int count = 0;
    if (row1 != row2 && col1 != col2) return -1;
    if (col1 == col2) {
        int _min = min(row1, row2);
        int _max = max(row1, row2);
        for (int i = _min + 1; i < _max; i++) {
            if (getStoneId(i, col1) != -1) count++;
        }
    } else {
        int _min = min(col1, col2);
        int _max = max(col1, col2);
        for (int i = _min + 1; i < _max; i++) {
            if (getStoneId(row1, i) != -1) count++;
        }
    }
    return count;
}

int Board::getdistance(int id, int row, int col) {
    int drow = abs(s[id].row - row);
    int dcol = abs(s[id].col - col);
    int d = drow * 10 + dcol;
    return d;
}

void Board::moveStone(int moveid, int row, int col) {
    s[moveid].row = row;
    s[moveid].col = col;
    redturn = !redturn;
}

void Board::moveStone(int moveid, int row, int col, int killid) {
    saveStep(moveid, row, col, killid, steps);
    moveStone(moveid, row, col);
    if (killid != -1) {
        s[killid].dead = true;
    }
}

void Board::saveStep(int i, int row, int col, int killid, QVector<Step *> &steps) {
    Step *step = new Step;
    step->moveid = i;
    step->colfrom = s[i].col;
    step->rowfrom = s[i].row;
    step->rowto = row;
    step->colto = col;
    step->killid = killid;
    steps.append(step);
}

void Board::backOne() {
    if (steps.size() == 0) return;
    Step *step = steps.last();
    steps.removeLast();
    if (step->killid != -1) s[step->killid].dead = false;
    moveStone(step->moveid, step->rowfrom, step->colfrom);
    delete step;
    update();
}

void Board::slotBack() {
    backOne();
}

void Board::drawInitPosition(QPainter &p) {
    drawInitPosition(p, 4, 1);
    drawInitPosition(p, 4, 3);
    drawInitPosition(p, 4, 5);
    drawInitPosition(p, 4, 7);
    drawInitPosition(p, 4, 9);

    drawInitPosition(p, 7, 1);
    drawInitPosition(p, 7, 3);
    drawInitPosition(p, 7, 5);
    drawInitPosition(p, 7, 7);
    drawInitPosition(p, 7, 9);

    drawInitPosition(p, 3, 2);
    drawInitPosition(p, 3, 8);

    drawInitPosition(p, 8, 2);
    drawInitPosition(p, 8, 8);
}

void Board::drawInitPosition(QPainter &p, int row, int col) {
    QPoint pt(col * d, row * d);
    QPoint off = QPoint(d / 12, d / 12);
    int len = d / 6;

    QPoint ptStart;
    QPoint ptEnd;

    if (col != 1) {
        /* 左上角 */
        ptStart = QPoint(pt.x() - off.x(), pt.y() - off.y());
        ptEnd = ptStart + QPoint(-len, 0);
        p.drawLine(ptStart, ptEnd);
        ptEnd = ptStart + QPoint(0, -len);
        p.drawLine(ptStart, ptEnd);

        /* 左下角 */
        ptStart = QPoint(pt.x() - off.x(), pt.y() + off.y());
        ptEnd = ptStart + QPoint(-len, 0);
        p.drawLine(ptStart, ptEnd);
        ptEnd = ptStart + QPoint(0, +len);
        p.drawLine(ptStart, ptEnd);
    }
    if (col != 9) {
        /* 右下角 */
        ptStart = QPoint(pt.x() + off.x(), pt.y() + off.y());
        ptEnd = ptStart + QPoint(+len, 0);
        p.drawLine(ptStart, ptEnd);
        ptEnd = ptStart + QPoint(0, +len);
        p.drawLine(ptStart, ptEnd);

        /* 右上角 */
        ptStart = QPoint(pt.x() + off.x(), pt.y() - off.y());
        ptEnd = ptStart + QPoint(+len, 0);
        p.drawLine(ptStart, ptEnd);
        ptEnd = ptStart + QPoint(0, -len);
        p.drawLine(ptStart, ptEnd);
    }
}