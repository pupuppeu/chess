//
// Created by Yongpu Jia on 2020/4/13.
//

#ifndef CHESS_STONE_H
#define CHESS_STONE_H


#include <QString>
#include <QPoint>
#include <QColor>

class Stone {
public:
    int id;
    int d;
    int row;
    int col;
    bool dead;
    bool red;
    QColor color;
    enum TYPE{JIANG,CHE,PAO,MA,BING,SHI,XIANG};
    TYPE type;

    QString getText();
    QPoint getcenter();
    void init(int _id);
};


#endif //CHESS_STONE_H
