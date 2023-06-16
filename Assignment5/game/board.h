#ifndef BOARD_H
#define BOARD_H

#include <fstream> // Required for file input/output operations

#include "block.h" // Include the Block class

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NOTHING
};

class Board
{
private:
    Block *block[4][4]; // 2D array to store the blocks on the board
    int score; // Variable to keep track of the score
public:
    Board(); // Constructor to initialize the board
    ~Board(); // Destructor to clean up resources

    void setBlock(int row, int col, int value);  // Method to set the value of a block at a specific position
    int getBlock(int row, int col) const { return block[row][col]->getValue(); }  // Method to get the value of a block at a specific position

    void setScore(int score) { this->score = score; }  // Method to set the score
    int getScore() const { return score; }  // Method to get the score

    bool movable(Direction direction);  // Method to check if the board is movable in a specific direction
    void move(Direction direction, std::ofstream& progress);  // Method to move the blocks on the board in a specific direction and update the progress

};

#endif // BOARD_H
