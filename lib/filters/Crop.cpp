#include "Crop.h"

Crop::Crop(int32_t width, int32_t height) : width_(width), height_(height) {

}

void Crop::Apply(Bmp &bmp) {
    height_ = std::min(height_, bmp.img_header.height);
    bmp.img_header.width = std::min(width_, bmp.img_header.width);
    Panel new_panel;
    new_panel.SetSize(bmp.img_header.height, bmp.img_header.width);
    for (int32_t h = bmp.img_header.height - height_; h < bmp.img_header.height; ++h) {
        for (int32_t w = 0; w < bmp.img_header.width; ++w) {
            new_panel.SetPixel(h, w, bmp.panel.GetPixel(h, w));
        }
    }
    bmp.img_header.height = height_;
    bmp.panel = new_panel;
}

Crop::~Crop() = default;
