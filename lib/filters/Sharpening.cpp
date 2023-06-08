#include "Sharpening.h"

const int parameter1 = 5;
const int parameter2 = -1;

void Sharpening::Apply(Bmp &bmp) {
    std::vector<std::vector<int>> matrix = {{0,          parameter2, 0},
                                            {parameter2, parameter1, parameter2},
                                            {0,          parameter2, 0}};
    ApplyMatrix(matrix, bmp);
}
