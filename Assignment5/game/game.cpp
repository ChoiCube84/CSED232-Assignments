#include <cstdlib>
#include <random>

#include "game.h"

Game::Game() : prev(nullptr), restore(3)
{
    progress.open("progress.txt");  // Open the progress file

    curr = new Board();  // Create a new instance of the Board for the current game state

    progress << "INITIAL ";  // Record the initial state

    spawn(true);  // Spawn the initial blocks
    progress << " ";

    spawn(true);
    progress << "\n";
}

Game::~Game()
{
    progress.close();  // Close the progress file
}

void Game::spawn(bool init)
{
    bool empty_exist = false;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (curr->getBlock(i, j) == 0)  // Check if any empty blocks exist on the board
                empty_exist = true;
        }
    }

    if (!empty_exist)
        return;  // If no empty blocks exist, return

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> zero_to_three(0, 3);
    std::uniform_int_distribution<int> zero_to_four(0, 4);

    int row, col, value;

    do
    {
        row = zero_to_three(gen);
        col = zero_to_three(gen);

        value = getValue(row, col);  // Get the value of the block at the randomly selected position

    } while (value != 0);

    if (init)
    {
        value = 2;
        progress << row + 1 << " " << col + 1;  // Record the initial block spawn position
    }
    else
    {
        int temp = zero_to_four(gen);
        if (temp == 4)
            value = 4;
        else
            value = 2;
        progress << "GENERATE " << row + 1 << " " << col + 1 << " " << value << "\n";  // Record the generated block position and value
    }

    curr->setBlock(row, col, value);  // Set the value of the spawned block on the board
}

bool Game::move(Direction direction)
{
    switch (direction)
    {
    case UP:
        progress << "UP\n";
        break;
    case DOWN:
        progress << "DOWN\n";
        break;
    case LEFT:
        progress << "LEFT\n";
        break;
    case RIGHT:
        progress << "RIGHT\n";
        break;
    default:
        break;
    }

    if (curr->movable(direction))
    {
        if (!prev_exist())
        {
            prev = new Board();  // Create a new instance of the Board for the previous game state
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                prev->setBlock(i, j, curr->getBlock(i, j));  // Save the current board state to the previous board state
            }
        }
        prev->setScore(curr->getScore());  // Save the current score to the previous score

        curr->move(direction, progress);  // Move the blocks on the board in the specified direction
        spawn();  // Spawn a new block
        return true;
    }
    else
        return false;
}

void Game::undo()
{
    delete curr;  // Delete the current board instance

    curr = new Board();  // Create a new instance of the Board for the current game state
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            curr->setBlock(i, j, prev->getBlock(i, j));  // Restore the previous board state to the current board state
        }
    }
    curr->setScore(prev->getScore());  // Restore the previous score to the current score

    delete prev;  // Delete the previous board instance
    prev = nullptr;

    restore--;  // Decrement the restore count

    progress << "RESTORE " << restore << "\n";  // Record the restore operation
}

void Game::scoreRecord()
{
    progress << "SCORE " << curr->getScore() << "\n";  // Record the current score
}

bool Game::win(int required)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (curr->getBlock(i, j) >= required)  // Check if any block value is equal to or greater than the required value for winning
                return true;
        }
    }
    return false;
}

bool Game::lose()
{
    return !(curr->movable(UP) || curr->movable(DOWN) || curr->movable(LEFT) || curr->movable(RIGHT));  // Check if the board is not movable in any direction, indicating a loss
}
