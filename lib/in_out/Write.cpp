#include "Write.h"

void Write::WriteByte(std::ofstream &out, uint8_t ch) {
    out.put(ch);
}

void Write::Write32(std::ofstream &out, int32_t value) {
    out.write(reinterpret_cast<char *>(&value), sizeof value);
}

void Write::Write16(std::ofstream &out, int16_t value) {
    out.write(reinterpret_cast<char *>(&value), sizeof value);
}

void Write::WritePixel(std::ofstream &out, Pixel &pixel) {
    WriteByte(out, pixel.red);
    WriteByte(out, pixel.green);
    WriteByte(out, pixel.blue);
}

void Write::WriteZeros(std::ofstream &out, int32_t count) {
    for (int32_t i = 0; i < count; ++i) {
        WriteByte(out, 0);
    }
}
