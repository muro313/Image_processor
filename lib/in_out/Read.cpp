#include "Read.h"

uint8_t Read::ReadByte(std::ifstream &in) {
    return static_cast<uint8_t>(in.get());
}

int32_t Read::Read32(std::ifstream &in) {
    int32_t res = 0;
    in.read(reinterpret_cast<char *>(&res), sizeof(res));
    return res;
}

int16_t Read::Read16(std::ifstream &in) {
    int16_t res = 0;
    in.read(reinterpret_cast<char *>(&res), sizeof(res));
    return res;
}

void Read::Skip(std::ifstream &in, int32_t count) {
    in.ignore(count);
}

Pixel Read::ReadPixel(std::ifstream &in) {
    Pixel pixel{
            .red = ReadByte(in),
            .green = ReadByte(in),
            .blue = ReadByte(in)
    };
    return pixel;
}
