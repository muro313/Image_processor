#pragma once
#include "../filters/facroty.h"


class Controller{
public:
    Controller(std::string input, std::string output,
               const std::vector<std::shared_ptr<Filter>>& filters);
    void Apply_all();
private:
    std::string input_;
    std::string output_;
    std::vector<std::shared_ptr<Filter>> filters_;
};

class Parser {
public:
    static Controller ArgParser(int argc, const char *argv[]);
};


