#include "ColorPanel.h"

void Panel::SetPixel(int32_t h, int32_t w, Pixel& new_pixel) {
    pixels[h][w] = new_pixel;
}

Pixel &Panel::GetPixel(int32_t h, int32_t w) {
    return pixels[h][w];
}

void Panel::SetSize(int32_t h, int32_t w) {
    width_ = w;
    height_ = h;
    std::vector<Pixel> row(w);
    pixels.resize(h, row);
    padding_amount_ = (4 - (width_ * 3) % 4) % 4;
}

int32_t Panel::height() const {
    return height_;
}

int32_t Panel::width() const {
    return width_;
}

int32_t Panel::padding_amount() const {
    return padding_amount_;
}
