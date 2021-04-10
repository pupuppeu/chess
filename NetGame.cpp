//
// Created by Yongpu Jia on 2020/4/14.
//

#include "NetGame.h"

NetGame::NetGame(bool asserver) : Board(asserver) {
    server = NULL;
    socket = NULL;
    if (asserver) {
        server = new QTcpServer(this);
        server->listen(QHostAddress::Any, 9999);
        connect(server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    } else {
        socket = new QTcpSocket(this);
        socket->connectToHost(QHostAddress("127.0.0.1"), 9999);
        connect(socket, SIGNAL(readyRead()), this, SLOT(slotRecv()));
    }
}

void NetGame::click(int id, int row, int col) {
    if (selectid == -1 && id != -1) {
        if (s[id].red != redside) {
            return;
        }
    }
    Board::click(id, row, col);
    if (socket != NULL) {
        char buf[3];
        buf[0] = id;
        buf[1] = 11 - row;
        buf[2] = 10 - col;
        socket->write(buf, 3);
    }
}

void NetGame::slotNewConnection() {
    if (socket) return;
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(slotRecv()));
}

void NetGame::slotRecv() {
    QByteArray ba = socket->readAll();
    if(ba.size()==1){
        backOne();
        backOne();
        return;
    }
    int id = ba[0];
    int row = ba[1];
    int col = ba[2];
    Board::click(id, row, col);
}

void NetGame::slotBack() {
    if(redturn!=redside) return;
    backOne();
    backOne();
    char buf[1];
    socket->write(buf,1);
}