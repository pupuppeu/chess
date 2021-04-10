//
// Created by Yongpu Jia on 2020/4/15.
//

#ifndef CHESS2_MAINWND_H
#define CHESS2_MAINWND_H


#include <QWidget>
#include <QPushButton>

class MainWnd : public QWidget {
public:
    MainWnd(int type);

    QPushButton *backbutton;
    int gametype;
};


#endif //CHESS2_MAINWND_H
