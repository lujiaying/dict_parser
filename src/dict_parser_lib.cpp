#include <fstream>

#include "dict_parser_lib.h"

namespace goodcoder {
    
int DictParser::init(const char* dict_pattern_file) {
    std::ifstream fin(dict_pattern_file);

    fin.close();
    return 0;
}


}
