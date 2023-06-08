#pragma once

#include "facroty.h"

class Grayscale : public Filter {
public:
    void Apply(Bmp &bmp) override;

    virtual ~Grayscale() = default;
};