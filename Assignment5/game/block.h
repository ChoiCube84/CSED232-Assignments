#ifndef BLOCK_H
#define BLOCK_H

class Block
{
private:
    int value; // Private member variable to store the value of the block
public:
    Block(int value); // Constructor to initialize the block with a value
    ~Block(); // Destructor to clean up resources

    void setValue(int value) { this->value = value; } // Setter method to set the value of the block
    int getValue() { return this->value; } // Getter method to retrieve the value of the block
};

#endif // BLOCK_H
