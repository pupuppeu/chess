//
// Created by Yongpu Jia on 2020/4/15.
//

#ifndef CHESS2_CHOOSEDLG_H
#define CHESS2_CHOOSEDLG_H


#include <QDialog>
#include <QPushButton>

class ChooseDlg : public QDialog {
    Q_OBJECT
public:
    ChooseDlg();
    QPushButton *buttons[4];
    int selected;

public slots:
    void slotClicked();
};


#endif //CHESS2_CHOOSEDLG_H
