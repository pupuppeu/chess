//
// Created by Yongpu Jia on 2020/4/14.
//

#ifndef CHESS_NETGAME_H
#define CHESS_NETGAME_H


#include "Board.h"
#include <QTcpserver>
#include <QTcpSocket>

class NetGame : public Board {
Q_OBJECT
public:
    QTcpServer *server;
    QTcpSocket *socket;

    NetGame(bool asserver);

    void click(int id, int row, int col);

public slots:

    void slotNewConnection();

    void slotRecv();

    void slotBack();
};


#endif //CHESS_NETGAME_H
