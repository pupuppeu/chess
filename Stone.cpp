//
// Created by Yongpu Jia on 2020/4/13.
//

#include "Stone.h"

QString Stone::getText() {
    switch (this->type) {
        case CHE:
            return "车";
        case MA:
            return "马";
        case XIANG:
            return "相";
        case SHI:
            return "士";
        case JIANG:
            return "将";
        case PAO:
            return "炮";
        case BING:
            return "兵";
    }
}

QPoint Stone::getcenter() {
    QPoint p;
    p.setX(col * d);
    p.setY(row * d);
    return p;
}

void Stone::init(int _id) {
    id = _id;
    d = 40;
    dead = false;
    struct {
        int row, col;
        Stone::TYPE type;
    } pos[16] = {
            {1, 1, Stone::CHE},
            {1, 2, Stone::MA},
            {1, 3, Stone::XIANG},
            {1, 4, Stone::SHI},
            {1, 5, Stone::JIANG},
            {1, 6, Stone::SHI},
            {1, 7, Stone::XIANG},
            {1, 8, Stone::MA},
            {1, 9, Stone::CHE},
            {3, 2, Stone::PAO},
            {3, 8, Stone::PAO},
            {4, 1, Stone::BING},
            {4, 3, Stone::BING},
            {4, 5, Stone::BING},
            {4, 7, Stone::BING},
            {4, 9, Stone::BING},
    };
    if (id < 16) {
        red = false;
        row = pos[id].row;
        col = pos[id].col;
        type = pos[id].type;
        color=Qt::black;
    } else {
        red = true;
        row = 11 - pos[id - 16].row;
        col = 10 - pos[id - 16].col;
        type = pos[id - 16].type;
        color=Qt::red;
    }
}