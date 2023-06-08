#pragma once

#include <cstdint>
#include <fstream>
#include "../ColorPanel/ColorPanel.h"

class Read {
public:
    static uint8_t ReadByte(std::ifstream& in);
    static int32_t Read32(std::ifstream& in);
    static int16_t Read16(std::ifstream& in);
    static void Skip(std::ifstream& in, int32_t count);
    static Pixel ReadPixel(std::ifstream& in);
};

