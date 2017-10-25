#ifndef GOODCODER_DICT_PARSER_LIB_H
#define GOODCODER_DICT_PARSER_LIB_H

#include <vector>
#include <string>

namespace goodcoder {

class DictParser {
public:
    int init(const char* dict_pattern_file);

    /**
    int clear();

    template <typename T>
    int parse(T& val);
    **/

private:
    std::vector<std::string> _dict_pattern;
};

}

#endif //GOODCODER_DICT_PARSER_LIB_H
