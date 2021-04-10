#include <iostream>
#include <QApplication>
#include <QMessageBox>
#include "Board.h"
#include "SingleGame.h"
#include "NetGame.h"
#include "ChooseDlg.h"
#include "MainWnd.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ChooseDlg dlg;
    if(dlg.exec() != QDialog::Accepted)
        return 0;
    MainWnd wnd(dlg.selected);
    wnd.show();
    return app.exec();
}
