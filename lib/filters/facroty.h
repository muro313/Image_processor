#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../bmp/FILE_INFO.h"

struct FilterDescription {
    std::string name;
    std::vector<std::string> parameters;
};

class Filter {
public:
    virtual void Apply(Bmp& bmp) = 0;

    void ApplyMatrix(const std::vector<std::vector<int>> &matrix, Bmp& bmp);// if filter is given by matrix

    Pixel GetPixel(int32_t h, int32_t w, Bmp& bmp);
};

class Factory {
public:
    static std::vector<std::shared_ptr<Filter>> Filters_Maker(
            std::vector<FilterDescription> &filter_descriptions);

private:
    static std::shared_ptr<Filter> Filter_Maker(const FilterDescription &filter_descriptions);
};