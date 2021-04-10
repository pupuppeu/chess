//
// Created by Yongpu Jia on 2020/4/15.
//

#include <QVBoxLayout>
#include "ChooseDlg.h"

ChooseDlg::ChooseDlg() {
    buttons[0] = new QPushButton("人机对战");
    buttons[1] = new QPushButton("自我对战");
    buttons[2] = new QPushButton("网络对战(服务端,执红先走)");
    buttons[3] = new QPushButton("网络对战(客户端,执黑后走)");
    QVBoxLayout *lay = new QVBoxLayout(this);
    for (int i = 0; i < 4; i++) {
        lay->addWidget(buttons[i]);
        connect(buttons[i], SIGNAL(clicked()), this, SLOT(slotClicked()));
    }
}

void ChooseDlg::slotClicked() {
    QObject *s = sender();
    for (int i = 0; i < 4; i++) {
        if (buttons[i] == s) {
            selected = i;
            break;
        }
    }
    accept();
}