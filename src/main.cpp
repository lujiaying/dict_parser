#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "dict_parser_lib.h"
#include "utils.h"

int main() {
    const char DICT_PATTERN_FILE[] = "./test/data/simple.dict";
    const char DICT_FILE[] = "./test/data/simple.txt";
    goodcoder::DictParser dp;
    goodcoder::DictParserRet::flag_t ret;

    ret = dp.init(DICT_PATTERN_FILE);
    if (ret != goodcoder::DictParserRet::SUCCESS) {
        std::cerr << "[ERROR] Init dict_pattern_file" << std::endl;
        exit(-1);
    }

    std::string line;
    std::ifstream fin(DICT_FILE);
    while (std::getline(fin, line)) {
        int a;
        int b;
        float c;
        dp.do_parse(line, 0, a);
        dp.do_parse(line, 1, b);
        dp.do_parse(line, 2, c);
        std::cout << a << " " << b << " " << c << std::endl;
    }

    return 0;
}
