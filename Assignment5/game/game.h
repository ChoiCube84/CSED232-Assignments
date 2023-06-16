#ifndef GAME_H
#define GAME_H

#include <fstream>
#include "board.h"

class Game
{
private:
    Board *curr;  // Pointer to the current board state
    Board *prev;  // Pointer to the previous board state

    int restore;  // Variable to keep track of the restore state

    std::ofstream progress;  // Output file stream to record game progress

public:
    Game();  // Constructor to initialize the game
    ~Game();  // Destructor to clean up resources

    void spawn(bool init = false);  // Method to spawn a new block on the board

    int getValue(int row, int col) const { return curr->getBlock(row, col); }  // Method to get the value of a block at a specific position

    int getScore() const { return curr->getScore(); }  // Method to get the current score
    int getRestore() const { return restore; }  // Method to get the restore state

    bool move(Direction direction);  // Method to move the blocks on the board in a specific direction

    bool prev_exist() const { return prev != nullptr; }  // Method to check if a previous board state exists
    void undo();  // Method to undo the last move and restore the previous board state

    void scoreRecord();  // Method to record the current score

    bool win(int required = 2048);  // Method to check if the player has won the game
    bool lose();  // Method to check if the player has lost the game
};

#endif // GAME_H
