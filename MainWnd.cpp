//
// Created by Yongpu Jia on 2020/4/15.
//

#include <QHBoxLayout>
#include "MainWnd.h"
#include "SingleGame.h"
#include "NetGame.h"

MainWnd::MainWnd(int type) {
    gametype = type;
    backbutton = new QPushButton("BACK");
    if (gametype == 0) {
        SingleGame *game = new SingleGame(true);
        QHBoxLayout *hlay = new QHBoxLayout(this);
        hlay->addWidget(game);
        hlay->addWidget(backbutton);
        connect(backbutton, SIGNAL(clicked()), game, SLOT(slotBack()));
    } else if (gametype == 1) {
        Board *game = new Board(true);
        QHBoxLayout *hlay = new QHBoxLayout(this);
        hlay->addWidget(game, 1);
        hlay->addWidget(backbutton);
        connect(backbutton, SIGNAL(clicked()), game, SLOT(slotBack()));
    } else if (gametype == 2) {
        NetGame *game = new NetGame(true);
        QHBoxLayout *hlay = new QHBoxLayout(this);
        hlay->addWidget(game, 1);
        hlay->addWidget(backbutton);
        connect(backbutton, SIGNAL(clicked()), game, SLOT(slotBack()));
    } else if (gametype == 3) {
        NetGame *game = new NetGame(false);
        QHBoxLayout *hlay = new QHBoxLayout(this);
        hlay->addWidget(game, 1);
        hlay->addWidget(backbutton);
        connect(backbutton,SIGNAL(clicked()),game,SLOT(slotBack()));
    }
}