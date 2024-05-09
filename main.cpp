#include "mainwindow.h"
#include "game_engine.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game_engine w;
    w.show();
    return a.exec();
}
