#include <string>
#include <QApplication>
#include <QTimer>
#include <QEventLoop>

#include "gameui.h"


GameUi::GameUi(Game *game)
    : QMainWindow{},
    game_board(new QGridLayout()),
    score(new QLabel("Score: 0")),
    restore(new QPushButton("Restore")),
    exit(new QPushButton("Exit")),
    game(game)
{
    initGameBoard();  // Initialize the game board UI
    QWidget *gameBoardWidget = new QWidget();
    gameBoardWidget->setLayout(game_board);

    initButton();  // Initialize the buttons

    QFont scoreFont;
    scoreFont.setPointSize(40);
    score->setFont(scoreFont);
    score->setAlignment(Qt::AlignCenter);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(score);
    vlayout->addStretch(1);
    vlayout->addWidget(restore);
    vlayout->addWidget(exit);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(gameBoardWidget);
    hlayout->addLayout(vlayout);

    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(hlayout);

    this->setCentralWidget(centralWidget);  // Set the central widget of the main window
}

void GameUi::initGameBoard()
{
    game_board->setSpacing(10);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            block[i][j] = new BlockUi();  // Create a new BlockUi object
            game_board->addWidget(block[i][j], i, j);  // Add the BlockUi object to the game board layout
        }
    }

    boardUpdate();  // Update the game board UI
}

void GameUi::initButton()
{
    restore->setFixedSize(300, 200);
    exit->setFixedSize(300, 200);
    restore->setFocusPolicy(Qt::NoFocus);
    exit->setFocusPolicy(Qt::NoFocus);

    QFont buttonFont;
    buttonFont.setPointSize(20);
    restore->setFont(buttonFont);
    exit->setFont(buttonFont);

    connect(restore, &QPushButton::clicked, this, &GameUi::onRestoreClicked);  // Connect the restore button's clicked signal to the corresponding slot
    connect(exit, &QPushButton::clicked, this, &GameUi::onExitClicked);  // Connect the exit button's clicked signal to the corresponding slot
}

void GameUi::onRestoreClicked()
{
    int restore_count = game->getRestore();

    if (!game->prev_exist()) {
        QMessageBox::information(this, "Restore", "There is no previously saved board in the buffer.");
    }
    else if (restore_count <= 0) {
        QMessageBox::information(this, "Restore", "No more chance to restore the board to its previous state.");
    }
    else {
        std::string question = "Restore the game board to its previous state?\n"
                               "\n"
                               "Remaining chances: " + std::to_string(restore_count);
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Restore", question.c_str(), QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            game->undo();
            QMessageBox::information(this, "Restore", "The board has been restored to its previous state!");
        }
    }

    scoreUpdate();  // Update the score display
    boardUpdate();  // Update the game board UI
}

void GameUi::onExitClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure to quit?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void GameUi::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        if (game->lose()) {
            std::string result = "You lose...\n"
                                 "\n"
                                 "Score: " + std::to_string(game->getScore());
            QMessageBox::information(this, "Lose", result.c_str());
            QApplication::quit();
        }
        else {
            if (game->move(eventToDirection(event))) {
                scoreUpdate();  // Update the score display
                boardUpdate();  // Update the game board UI
                winCheck();  // Check if the player has won the game
            }
        }
        break;
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
}

Direction GameUi::eventToDirection(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        return UP;
    case Qt::Key_Down:
        return DOWN;
    case Qt::Key_Left:
        return LEFT;
    case Qt::Key_Right:
        return RIGHT;
    default:
        return NOTHING;
    }
}

void GameUi::scoreUpdate()
{
    game->scoreRecord();  // Record the current score

    QString scoreText("Score: ");
    scoreText.append(std::to_string(game->getScore()).c_str());
    score->setText(scoreText);  // Update the score display
}

void GameUi::boardUpdate()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            block[i][j]->blockUpdate(game->getValue(i, j));  // Update each block on the game board
        }
    }
}

void GameUi::winCheck()
{
    if (game->win(2048)) {
        QEventLoop loop;

        QTimer::singleShot(0, [&loop]() {
            loop.quit();
        });

        QTimer::singleShot(1000, [this]() {
            std::string result = "Congratulation!\n"
                                 "\n"
                                 "Score: " + std::to_string(game->getScore());
            QMessageBox::information(this, "Win", result.c_str());
            QApplication::quit();
        });

        loop.exec();
    }
}
