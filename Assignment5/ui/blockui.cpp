#include <QString>

#include "blockui.h"

BlockUi::BlockUi()
{
    setFixedSize(250, 250);  // Set the fixed size of the block
    setAlignment(Qt::AlignCenter);  // Set the alignment of the block's contents
    setStyleSheet("QLabel { background: rgb(255, 255, 255); color: black; border style: solid; font: 70pt; font: bold; }");  // Set the initial style sheet of the block
}

std::array<int, 3> BlockUi::getRGB(int value) {
    std::array<int, 3> result;

    switch(value) {
    case 2:
        result[0] = 187;
        result[1] = 173;
        result[2] = 160;
        break;
    case 4:
        result[0] = 237;
        result[1] = 224;
        result[2] = 200;
        break;
    case 8:
        result[0] = 242;
        result[1] = 177;
        result[2] = 121;
        break;
    case 16:
        result[0] = 245;
        result[1] = 149;
        result[2] = 99;
        break;
    case 32:
        result[0] = 246;
        result[1] = 126;
        result[2] = 95;
        break;
    case 64:
        result[0] = 246;
        result[1] = 94;
        result[2] = 59;
        break;
    case 128:
        result[0] = 237;
        result[1] = 207;
        result[2] = 114;
        break;
    case 256:
        result[0] = 237;
        result[1] = 204;
        result[2] = 97;
        break;
    case 512:
        result[0] = 237;
        result[1] = 200;
        result[2] = 80;
        break;
    case 1024:
        result[0] = 237;
        result[1] = 197;
        result[2] = 63;
        break;
    case 2048:
        result[0] = 237;
        result[1] = 194;
        result[2] = 46;
        break;
    default:
        result[0] = 255;
        result[1] = 255;
        result[2] = 255;
        break;
    }
    return result;
}

void BlockUi::blockUpdate(int value)
{
    std::array<int, 3> color = getRGB(value);

    QString style = "QLabel { background: rgb(";
    style.append(std::to_string(color[0]).c_str());
    style.append(", ");
    style.append(std::to_string(color[1]).c_str());
    style.append(", ");
    style.append(std::to_string(color[2]).c_str());
    style.append("); color: black; border style: solid; font: 70pt; font: bold; }");  // Update the style sheet of the block with the corresponding color

    setStyleSheet(style);

    if (value != 0)
        setText(std::to_string(value).c_str());  // If the value is not zero, set the text of the block to the value
    else
        setText("");  // If the value is zero, clear the text of the block
}
