#pragma once

#include "facroty.h"

class Sharpening : public Filter {
public:
    void Apply(Bmp &bmp) override;

    virtual ~Sharpening() = default;
};