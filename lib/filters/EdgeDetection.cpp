#include "EdgeDetection.h"

const int max = 255;

void EdgeDetection::Apply(Bmp &bmp) {
    std::vector<std::vector<int>> matrix = {{0,  -1, 0},
                                            {-1, 4,  -1},
                                            {0,  -1, 0}};
    ApplyMatrix(matrix, bmp);
    for (int32_t height = 0; height < bmp.panel.height(); ++height) {
        for (int32_t width = 0; width < bmp.panel.width(); ++width) {
            Pixel pixel = bmp.panel.GetPixel(height, width);
            if (static_cast<float>(pixel.blue) / 225.0f > threshold_) {
                pixel.blue = max;
            } else {
                pixel.blue = 0;
            }
            pixel.red = pixel.blue;
            pixel.green = pixel.red;
        }
    }
}

EdgeDetection::EdgeDetection(const float threshold) : threshold_(threshold) {
}
