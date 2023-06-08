#pragma once
#include <fstream>
#include "../ColorPanel/ColorPanel.h"
class Write {
public:
    static void WriteByte(std::ofstream& out, uint8_t ch);

    static void Write32(std::ofstream& out, int32_t value);

    static void Write16(std::ofstream& out, int16_t value);

    static void WritePixel(std::ofstream& out, Pixel& pixel);

    static void WriteZeros(std::ofstream& out, int32_t count);
};
