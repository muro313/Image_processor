#include "Grayscale.h"

const double RED_COEF = 0.299;
const double GREEN_COEF = 0.587;
const double BLUE_COEF = 0.114;

void Grayscale::Apply(Bmp &bmp) {
    for (int32_t h = 0; h < bmp.panel.height(); ++h) {
        for (int32_t w = 0; w < bmp.panel.width(); ++w) {
            Pixel new_pixel = bmp.panel.GetPixel(h, w);
            new_pixel.green = static_cast<uint8_t>(RED_COEF * static_cast<double>(new_pixel.red)
                                                   + GREEN_COEF * static_cast<double>(new_pixel.green) +
                                                   BLUE_COEF * static_cast<double>(new_pixel.blue));
            new_pixel.blue = new_pixel.green;
            new_pixel.red = new_pixel.blue;
            bmp.panel.SetPixel(h, w, new_pixel);
        }
    }
}
