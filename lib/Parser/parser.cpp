#include "parser.h"
#include <exception>

Controller Parser::ArgParser(int argc, const char *argv[]) {
    if (argc < 2) {
        throw std::runtime_error("Invalid arguments: Not enough arguments.");
    }
    std::vector<FilterDescription> descriptions;
    FilterDescription description;
    for (size_t i = 3; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if (!description.name.empty()) { //at least one des
                descriptions.push_back(description);
            }
            description.parameters.clear();
            description.name = argv[i];
        } else {
            description.parameters.emplace_back(argv[i]);
        }
    }
    descriptions.push_back(description);
    auto filters = Factory::Filters_Maker(descriptions);
    return {argv[1], argv[2], filters};
}

Controller::Controller(std::string input,
                       std::string output,
                       const std::vector<std::shared_ptr<Filter>> &filters)
        : input_(std::move(input)),
          output_(std::move(output)),
          filters_(filters) {
}

void Controller::Apply_all() {
    std::ifstream in(input_,
                     std::ios::in | std::ios::binary);
    if(!in.good()){
        throw std::runtime_error("Cannot open input file.");
    }
    Bmp bmp(in);

    for ( const auto& filter: filters_) {
        filter->Apply(bmp);
    }
    std::ofstream out(output_, std::ios::out | std::ios::binary);
    if(!out.good()){
        throw std::runtime_error("Cannot open or create output file.");
    }
    bmp.Save(out);
}
