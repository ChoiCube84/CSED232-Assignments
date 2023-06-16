#ifndef BLOCKUI_H
#define BLOCKUI_H

#include <string>
#include <array>
#include <QLabel>

class BlockUi : public QLabel
{
    Q_OBJECT
public:
    BlockUi();  // Constructor to initialize the BlockUi

    std::array<int, 3> getRGB(int value);  // Method to get the RGB color values based on the block value
    void blockUpdate(int value);  // Method to update the block UI with a new value
};

#endif // BLOCKUI_H
