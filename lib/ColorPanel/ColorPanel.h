#pragma once

#include <cstdint>
#include <vector>

struct Pixel{
    uint8_t red;
    uint8_t  green;
    uint8_t blue;
};

class Panel{
public:
    void SetSize(int32_t h, int32_t w);
    void SetPixel(int32_t h, int32_t w, Pixel& new_pixel);
    Pixel& GetPixel(int32_t h, int32_t w);
    int32_t height() const;
    int32_t width() const;
    int32_t padding_amount() const;
private:
    int32_t height_ = 0;
    int32_t width_ = 0;
    int32_t padding_amount_;
    std::vector<std::vector<Pixel>> pixels;
};