#include "board.h"

Board::Board() : score(0)
{
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            block[i][j] = new Block(0);  // Initialize each block with a value of 0
        }
    }
}

Board::~Board()
{
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            delete block[i][j];  // Deallocate memory for each block
        }
    }
}

void Board::setBlock(int row, int col, int value)
{
    block[row][col]->setValue(value);  // Set the value of the block at the specified position
}

bool Board::movable(Direction direction)
{
    switch(direction) {
    case UP:
    case DOWN:
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 3; j++) {
                if(
                    (block[j][i]->getValue() == block[j+1][i]->getValue()) ||  // Check if adjacent blocks have the same value
                    (block[j][i]->getValue() == 0 && block[j+1][i]->getValue() != 0) ||  // Check if one block is empty and the other is not
                    (block[j][i]->getValue() != 0 && block[j+1][i]->getValue() == 0)  // Check if one block is not empty and the other is
                    ) {
                    return true;  // Board is movable in the specified direction
                }
            }
        }
        break;
    case LEFT:
    case RIGHT:
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 3; j++) {
                if(
                    (block[i][j]->getValue() == block[i][j+1]->getValue()) ||  // Check if adjacent blocks have the same value
                    (block[i][j]->getValue() == 0 && block[i][j+1]->getValue() != 0) ||  // Check if one block is empty and the other is not
                    (block[i][j]->getValue() != 0 && block[i][j+1]->getValue() == 0)  // Check if one block is not empty and the other is
                    ) {
                    return true;  // Board is movable in the specified direction
                }
            }
        }
        break;
    default:
        return false;
    }
    return false;  // Board is not movable in the specified direction
}

void Board::move(Direction direction, std::ofstream& progress)
{
    if(!movable(direction))
        return;  // If the board is not movable in the specified direction, return without making any changes

    int temp[4][4];

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            temp[i][j] = block[i][j]->getValue();  // Copy the values of the blocks to a temporary array
            block[i][j]->setValue(0);  // Set the values of all blocks to 0
        }
    }

    switch(direction)
    {
    case UP:
        for(int i = 0; i < 4; i++)
        {
            int pos = 0;
            for(int j = 0; j < 4; j++)
            {
                if(temp[j][i] != 0)
                {
                    if(block[pos][i]->getValue() == 0)
                    {
                        block[pos][i]->setValue(temp[j][i]);  // Move the block to the topmost position in the column
                    }
                    else if(block[pos][i]->getValue() == temp[j][i])
                    {
                        block[pos][i]->setValue(temp[j][i] * 2);  // Merge the block with the topmost block in the column
                        score += temp[j][i] * 2;  // Update the score

                        progress << "MERGE " << pos + 1 << " " << i + 1 << " " << temp[j][i] * 2 << "\n";  // Write the merge operation to the progress file

                        pos++;
                    }
                    else
                    {
                        pos++;
                        block[pos][i]->setValue(temp[j][i]);  // Move the block to the next available position in the column
                    }
                }
            }
        }
        break;
    case DOWN:
        for(int i = 0; i < 4; i++)
        {
            int pos = 3;
            for(int j = 3; j >= 0; j--)
            {
                if(temp[j][i] != 0)
                {
                    if(block[pos][i]->getValue() == 0)
                    {
                        block[pos][i]->setValue(temp[j][i]);  // Move the block to the bottommost position in the column
                    }
                    else if(block[pos][i]->getValue() == temp[j][i])
                    {
                        block[pos][i]->setValue(temp[j][i] * 2);  // Merge the block with the bottommost block in the column
                        score += temp[j][i] * 2;  // Update the score

                        progress << "MERGE " << pos + 1 << " " << i + 1 << " " << temp[j][i] * 2 << "\n";  // Write the merge operation to the progress file

                        pos--;
                    }
                    else
                    {
                        pos--;
                        block[pos][i]->setValue(temp[j][i]);  // Move the block to the next available position in the column
                    }
                }
            }
        }
        break;
    case LEFT:
        for(int i = 0; i < 4; i++)
        {
            int pos = 0;
            for(int j = 0; j < 4; j++)
            {
                if(temp[i][j] != 0)
                {
                    if(block[i][pos]->getValue() == 0)
                    {
                        block[i][pos]->setValue(temp[i][j]);  // Move the block to the leftmost position in the row
                    }
                    else if(block[i][pos]->getValue() == temp[i][j])
                    {
                        block[i][pos]->setValue(temp[i][j] * 2);  // Merge the block with the leftmost block in the row
                        score += temp[i][j] * 2;  // Update the score

                        progress << "MERGE " << i + 1 << " " << pos + 1 << " " << temp[i][j] * 2 << "\n";  // Write the merge operation to the progress file

                        pos++;
                    }
                    else
                    {
                        pos++;
                        block[i][pos]->setValue(temp[i][j]);  // Move the block to the next available position in the row
                    }
                }
            }
        }
        break;
    case RIGHT:
        for(int i = 0; i < 4; i++)
        {
            int pos = 3;
            for(int j = 3; j >= 0; j--)
            {
                if(temp[i][j] != 0)
                {
                    if(block[i][pos]->getValue() == 0)
                    {
                        block[i][pos]->setValue(temp[i][j]);  // Move the block to the rightmost position in the row
                    }
                    else if(block[i][pos]->getValue() == temp[i][j])
                    {
                        block[i][pos]->setValue(temp[i][j] * 2);  // Merge the block with the rightmost block in the row
                        score += temp[i][j] * 2;  // Update the score

                        progress << "MERGE " << i + 1 << " " << pos + 1 << " " << temp[i][j] * 2 << "\n";  // Write the merge operation to the progress file

                        pos--;
                    }
                    else
                    {
                        pos--;
                        block[i][pos]->setValue(temp[i][j]);  // Move the block to the next available position in the row
                    }
                }
            }
        }
        break;
    default:
        break;
    }
}

