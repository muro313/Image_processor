#pragma once

#include "facroty.h"

class Negative : public Filter {
public:
    void Apply(Bmp &bmp) override;

    virtual ~Negative() = default;
};

