#pragma once

#include "facroty.h"

class EdgeDetection : public Filter {
public:
    explicit EdgeDetection(float threshold);

    void Apply(Bmp &bmp) override;

    virtual ~EdgeDetection() = default;

private:
    float threshold_;
};
