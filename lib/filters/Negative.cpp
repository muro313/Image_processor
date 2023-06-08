#include "Negative.h"

const uint8_t max = 255;

void Negative::Apply(Bmp &bmp) {
    for (int32_t h = 0; h < bmp.panel.height(); ++h) {
        for (int32_t w = 0; w < bmp.panel.width(); ++w) {
            Pixel new_pixel = bmp.panel.GetPixel(h, w);
            new_pixel.green = max -  new_pixel.green;
            new_pixel.red = max -  new_pixel.red;
            new_pixel.blue = max -  new_pixel.blue;
            bmp.panel.SetPixel(h, w, new_pixel);
        }
    }
}
