#ifndef GAMEUI_H
#define GAMEUI_H

#include <QMainWindow>
#include <QGridLayout>
#include <QFont>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QMessageBox>
#include <QWidget>

#include "blockui.h"
#include "../game/game.h"

class GameUi : public QMainWindow
{
    Q_OBJECT

private:
    QGridLayout *game_board;  // Grid layout to hold the game board
    QLabel *score;  // Label to display the score
    QPushButton *restore;  // Button to restore a previous game state
    QPushButton *exit;  // Button to exit the game

    BlockUi *block[4][4];  // 2D array of BlockUi objects to represent the blocks on the game board

    Game *game;  // Pointer to the Game object

public:
    GameUi(Game *game);  // Constructor to initialize the GameUi with a Game object

protected:
    void keyPressEvent(QKeyEvent *event) override;  // Event handler for key press events

private:
    void initGameBoard();  // Method to initialize the game board layout
    void initButton();  // Method to initialize the buttons

    void onRestoreClicked();  // Slot for restore button click event
    void onExitClicked();  // Slot for exit button click event

    Direction eventToDirection(QKeyEvent *event);  // Method to convert key press events to Direction enum values

    void scoreUpdate();  // Method to update the score display
    void boardUpdate();  // Method to update the game board UI
    void winCheck();  // Method to check if the player has won the game
};

#endif // GAMEUI_H
