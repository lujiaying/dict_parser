#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "dict_parser_lib.h"
#include "utils.h"

int main() {
    goodcoder::DictParser dp;
    std::cout << "hello world" << std::endl;

    std::ifstream fin("./test/data/simple.txt");
    std::vector<std::string> v;
    std::string line;
    while (std::getline(fin, line)) {
        std::cout << line << std::endl;
    }
    return 0;
}
