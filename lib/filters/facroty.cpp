#include "facroty.h"
#include "Crop.h"
#include "Grayscale.h"
#include "Negative.h"
#include "Sharpening.h"
#include "EdgeDetection.h"

int const max = 255;
int const min = 0;

std::vector<std::shared_ptr<Filter>> Factory::Filters_Maker(
        std::vector<FilterDescription> &filter_descriptions) {
    std::vector<std::shared_ptr<Filter>> filters;
    filters.reserve(filter_descriptions.size());
    for (const auto &description: filter_descriptions) {
        filters.push_back(Filter_Maker(description));
    }
    return filters;
}

std::shared_ptr<Filter> Factory::Filter_Maker(const FilterDescription &filter_description) {
    if (filter_description.name == "-crop") {
        if (filter_description.parameters.size() != 2) {
            throw std::runtime_error("Invalid argument: Filters: Invalid arguments of filter crop.");
        }
        auto width = static_cast<int32_t>(std::stoll(filter_description.parameters[0]));
        auto height = static_cast<int32_t>(std::stoll(filter_description.parameters[1]));
        return std::make_shared<Crop>(width, height);
    }
    if (filter_description.name == "-gs") {
        if (!filter_description.parameters.empty()) {
            throw std::runtime_error("Invalid argument: Filters: Invalid arguments for filter grayscale.");
        }
        return std::make_shared<Grayscale>();
    }
    if (filter_description.name == "-neg") {
        if (!filter_description.parameters.empty()) {
            throw std::runtime_error("Invalid argument: Filters: Invalid arguments for filter negative.");
        }
        return std::make_shared<Negative>();
    }
    if (filter_description.name == "-sharp") {
        if (!filter_description.parameters.empty()) {
            throw std::runtime_error("Invalid argument: Filters: Invalid arguments for filter sharp.");
        }
        return std::make_shared<Sharpening>();
    }
    if (filter_description.name == "-edge") {
        if (filter_description.parameters.size() != 1) {
            throw std::runtime_error("Invalid argument: Filters: Invalid arguments for filter Edge Detection.");
        }
        return std::make_shared<EdgeDetection>(std::stof(filter_description.parameters[0]));
    }
    throw std::runtime_error("Invalid argument: Filters: Filter not found.");
}

void Filter::ApplyMatrix(const std::vector<std::vector<int>> &matrix, Bmp &bmp) {
    Panel new_panel;
    new_panel.SetSize(bmp.panel.height(), bmp.panel.width());
    for (int32_t h = 0; h < bmp.panel.height(); ++h) {
        for (int32_t w = 0; w < bmp.panel.width(); ++w) {
            int red =
                    matrix[0][0] * GetPixel(h - 1, w - 1, bmp).red +
                    matrix[0][1] * GetPixel(h - 1, w, bmp).red +
                    matrix[0][2] * GetPixel(h - 1, w + 1, bmp).red +
                    matrix[1][0] * GetPixel(h, w - 1, bmp).red +
                    matrix[1][1] * GetPixel(h, w, bmp).red +
                    matrix[1][2] * GetPixel(h, w + 1, bmp).red +
                    matrix[2][0] * GetPixel(h + 1, w - 1, bmp).red +
                    matrix[2][1] * GetPixel(h + 1, w, bmp).red +
                    matrix[2][2] * GetPixel(h + 1, w + 1, bmp).red;
            int green =
                    matrix[0][0] * GetPixel(h - 1, w - 1, bmp).green +
                    matrix[0][1] * GetPixel(h - 1, w, bmp).green +
                    matrix[0][2] * GetPixel(h - 1, w + 1, bmp).green +
                    matrix[1][0] * GetPixel(h, w - 1, bmp).green +
                    matrix[1][1] * GetPixel(h, w, bmp).green +
                    matrix[1][2] * GetPixel(h, w + 1, bmp).green +
                    matrix[2][0] * GetPixel(h + 1, w - 1, bmp).green +
                    matrix[2][1] * GetPixel(h + 1, w, bmp).green +
                    matrix[2][2] * GetPixel(h + 1, w + 1, bmp).green;
            int blue =
                    matrix[0][0] * GetPixel(h - 1, w - 1, bmp).blue +
                    matrix[0][1] * GetPixel(h - 1, w, bmp).blue +
                    matrix[0][2] * GetPixel(h - 1, w + 1, bmp).blue +
                    matrix[1][0] * GetPixel(h, w - 1, bmp).blue +
                    matrix[1][1] * GetPixel(h, w, bmp).blue +
                    matrix[1][2] * GetPixel(h, w + 1, bmp).blue +
                    matrix[2][0] * GetPixel(h + 1, w - 1, bmp).blue +
                    matrix[2][1] * GetPixel(h + 1, w, bmp).blue +
                    matrix[2][2] * GetPixel(h + 1, w + 1, bmp).blue;
            red = std::min(max, red);
            red = std::max(min, red);
            green = std::min(max, green);
            green = std::max(min, green);
            blue = std::min(max, blue);
            blue = std::max(min, blue);
            Pixel pixel{static_cast<uint8_t>(red),
                        static_cast<uint8_t>(green),
                        static_cast<uint8_t>(blue)};
            new_panel.SetPixel(h, w, pixel);
        }
    }
    bmp.panel = new_panel;
}

Pixel Filter::GetPixel(int32_t h, int32_t w, Bmp &bmp) {
    return bmp.panel.GetPixel(
            std::max(0, std::min(h, bmp.panel.height() - 1)),
            std::max(0, std::min(w, bmp.panel.width() - 1))
    );
}
