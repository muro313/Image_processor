#include "lib/Parser/parser.h"

int main(int argc, const char *argv[]) {
    Controller controller = Parser::ArgParser(argc, argv);
    controller.Apply_all();
}