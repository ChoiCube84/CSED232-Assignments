#include <QApplication>
#include <QMainWindow>
#include <QWidget>

#include "ui/gameui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Game game;
    GameUi gameui(&game);

    gameui.resize(1300, 1000);
    gameui.show();

    return app.exec();
}
