#include "stdlib.h"
#include <limits>
#include "dict_parser_lib.h"

namespace goodcoder {
    
DictParserRet::flag_t DictParser::init(const char* dict_pattern_file) {
    _fin.open(dict_pattern_file);
    if (!_fin.is_open()) {
        std::cerr << "[ERROR] Dict pattern file " << dict_pattern_file  << " open failed" << std::endl;
        return DictParserRet::EXIT;
    }
    // check pattern format
    if (!_is_pattern_file_valid()) {
        std::cerr << "[ERROR] Dict pattern file " << dict_pattern_file  << " format invalid" << std::endl;
        return DictParserRet::EXIT;
    }
    
    split(_dict_pattern_v, _dict_pattern_buf, DICT_DELIMITER);
    if (_dict_pattern_v.size() <= 0) {
        std::cerr << "[ERROR] Process dict pattern file failed" << std::endl;
        return DictParserRet::EXIT;
    }

    _fin.close();
    return DictParserRet::SUCCESS;
}

bool DictParser::_is_pattern_file_valid() {
    const int MAX_LINE_CNT = 1;
    // check dict content
    std::getline(_fin, _dict_pattern_buf);
    if (_dict_pattern_buf.size() == 0) {
        return false;
    }
    // check line count
    int line_cnt = 1;
    std::string line;
    while (std::getline(_fin, line)) {
        ++line_cnt;
    }
    if (line_cnt != MAX_LINE_CNT) {
        return false;
    } 

    _fin.clear();
    _fin.seekg(0, _fin.beg);
    return true;
}

DictParserRet::flag_t DictParser::_parse_built_in(const int& index, int& val) {
    long v;
    DictParserRet::flag_t ret = _parse_built_in(index, v);
    if (ret != DictParserRet::SUCCESS) {
        return ret;
    }
    if (v > std::numeric_limits<int>::max()) {
        val = std::numeric_limits<int>::max();
        return DictParserRet::OVERFLOW;
    } else if (v < std::numeric_limits<int>::lowest()) {
        val = std::numeric_limits<int>::lowest();
        return DictParserRet::OVERFLOW;
    } else {
        val = static_cast<int>(v);
        return DictParserRet::SUCCESS;
    }
}

DictParserRet::flag_t DictParser::_parse_built_in(const int& index, long& val) {
    char* p_end;
    errno = 0;
    val = strtol(_row_v[index].c_str(), &p_end, 0);
    if (errno == ERANGE) {
        val = 0;
        return DictParserRet::OVERFLOW;
    }
    if (_row_v[index].size() == 0 || *p_end != '\0') {
        val = 0;
        return DictParserRet::INCONVERTIBLE;
    }
    return DictParserRet::SUCCESS;
}

DictParserRet::flag_t DictParser::_parse_built_in(const int& index, float& val) {
    double v;
    DictParserRet::flag_t ret = _parse_built_in(index, v);
    if (ret != DictParserRet::SUCCESS) {
        return ret;
    }
    if (v > std::numeric_limits<float>::max()) {
        val = std::numeric_limits<float>::max();
        return DictParserRet::OVERFLOW;
    } else if (v < std::numeric_limits<float>::lowest()) {
        val = std::numeric_limits<float>::lowest();
        return DictParserRet::OVERFLOW;
    } else {
        val = static_cast<float>(v);
        return DictParserRet::SUCCESS;
    }
}

DictParserRet::flag_t DictParser::_parse_built_in(const int& index, double& val) {
    char* p_end;
    errno = 0;
    val = strtod(_row_v[index].c_str(), &p_end);
    if (errno == ERANGE) {
        val = 0.0;   
        return DictParserRet::OVERFLOW;
    }
    if (_row_v[index].size() == 0 || *p_end != '\0') {
        val = 0.0;
        return DictParserRet::INCONVERTIBLE;
    }
    return DictParserRet::SUCCESS;
}

DictParserRet::flag_t DictParser::_parse_built_in(const int& index, std::string& val) {
    val = _row_v[index];
    return DictParserRet::SUCCESS;
} 

}
