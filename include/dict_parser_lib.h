#ifndef GOODCODER_DICT_PARSER_LIB_H
#define GOODCODER_DICT_PARSER_LIB_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "utils.h"

namespace goodcoder {

const std::string DICT_DELIMITER("\t");

struct DictParserRet {
    enum flag_t { 
        EXIT,
        SUCCESS,
        FAIL,
        OVERFLOW,
        INCONVERTIBLE
    };
};

class DictParser {
public:
    DictParserRet::flag_t init(const char* dict_pattern_file);

    template <typename T>
    DictParserRet::flag_t do_parse(const std::string& row, const int& index, T& val) {
        DictParserRet::flag_t ret = _check_parse_valid(row, index, val);
        if (ret != DictParserRet::SUCCESS) {
            return ret;
        }
        return _parse_built_in(index, val);
    };

    /**
    int clear();
    **/

private:
    bool _is_pattern_file_valid();

    template <typename T>
    DictParserRet::flag_t _check_parse_valid(const std::string& row, const int& index, T& val) {
        if (index >= _dict_pattern_v.size()) {
            std::cerr << "index:" << index << " exceed dict_pattern length"<< std::endl;
            return DictParserRet::EXIT;
        }
        if (row != _row_buf) {
            _row_buf = row;
            split(_row_v, _row_buf, DICT_DELIMITER);
            if (_row_v.size() != _dict_pattern_v.size()) {
                return DictParserRet::FAIL;
            }
        }

        if (_dict_pattern_v[index] == "int") {
            if (!(typeid(val) == typeid(int)) && !(typeid(val) == typeid(long))) {
                std::cerr << "val type sholud be [int] or [long]" << std::endl;
                return DictParserRet::EXIT;
            }
        } else if (_dict_pattern_v[index] == "float") {
            if (!(typeid(val) == typeid(float)) && !(typeid(val) == typeid(double))) {
                std::cerr << "val type sholud be [float] or [double]" << std::endl;
                return DictParserRet::EXIT;
            }
        } else if (_dict_pattern_v[index] == "string") {
            if (!(typeid(val) == typeid(std::string))) {
                std::cerr << "val type sholud be [string]" << std::endl;
                return DictParserRet::EXIT;
            }
        } else {
            std::cerr << _dict_pattern_v[index] << " is not built-in type" << std::endl;
            return DictParserRet::EXIT;
        }
        return DictParserRet::SUCCESS;
    };

    DictParserRet::flag_t _parse_built_in(const int& index, int& val);
    DictParserRet::flag_t _parse_built_in(const int& index, long& val);
    DictParserRet::flag_t _parse_built_in(const int& index, float& val);
    DictParserRet::flag_t _parse_built_in(const int& index, double& val);
    DictParserRet::flag_t _parse_built_in(const int& index, std::string& val);

private:
    std::ifstream _fin;
    std::string _dict_pattern_buf;
    std::vector<std::string> _dict_pattern_v;
    std::string _row_buf;
    std::vector<std::string> _row_v;
};

}

#endif //GOODCODER_DICT_PARSER_LIB_H
