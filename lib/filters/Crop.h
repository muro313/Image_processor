#pragma once

#include "facroty.h"

class Crop : public Filter {
public:
    Crop(int32_t width, int32_t height);

    void Apply(Bmp& bmp) override;

    virtual ~Crop();

private:
    int32_t width_;
    int32_t height_;
};
