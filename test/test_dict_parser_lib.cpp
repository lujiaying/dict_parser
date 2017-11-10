#include <fstream>
#include <string>
#include <cstdio>

#include "gtest/gtest.h"
#include "dict_parser_lib.h"

namespace goodcoder_test {

const char DICT_PATTERN_FILE[] = "./simple.dict";
const char DICT_DATA_FILE[] = "./simple.txt";

class DictParserTest : public ::testing::Test {
protected:

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
        
        // Generate Test Data Files
        // Generate dict pattern file
        std::ofstream _fout(DICT_PATTERN_FILE);
        _fout << "int	int	float	string";
        _fout.close();
        // Generate dict data file
        _fout.open(DICT_DATA_FILE);
        _fout << "1	-1	2.1	2.222\n";
        _fout << "2	2	-3.62	aab\n";
        _fout << "	3	4.32	1a2b3c\n";
        _fout << "4	4.0	5.11	\n";
        _fout.close();
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
        std::remove(DICT_PATTERN_FILE);
        std::remove(DICT_DATA_FILE);
    }

    // Objects declared here can be used by all tests in the test case for Foo.
    goodcoder::DictParser _dp;
};


TEST_F(DictParserTest, IsInitOK) {
    goodcoder::DictParserRet::flag_t ret = _dp.init(DICT_PATTERN_FILE);
    EXPECT_EQ(ret, goodcoder::DictParserRet::SUCCESS);
}

TEST_F(DictParserTest, IsParseOK) {
    goodcoder::DictParserRet::flag_t ret = _dp.init(DICT_PATTERN_FILE);
    EXPECT_EQ(ret, goodcoder::DictParserRet::SUCCESS);
    std::ifstream fin(DICT_DATA_FILE);
    std::string line;
    int a;
    int b;
    float c;
    std::string s;

    // Line #1
    std::getline(fin, line);
    _dp.do_parse(line, 0, a);
    _dp.do_parse(line, 1, b);
    _dp.do_parse(line, 2, c);
    _dp.do_parse(line, 3, s);
    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, -1);
    EXPECT_FLOAT_EQ(c, 2.1);
    EXPECT_STREQ(s.c_str(), "2.222");
    // Line #2
    std::getline(fin, line);
    _dp.do_parse(line, 0, a);
    _dp.do_parse(line, 1, b);
    ret = _dp.do_parse(line, 2, c);
    _dp.do_parse(line, 3, s);
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 2);
    EXPECT_EQ(ret, goodcoder::DictParserRet::SUCCESS);
    EXPECT_FLOAT_EQ(c, -3.62);
    EXPECT_STREQ(s.c_str(), "aab");
    // Line #3
    std::getline(fin, line);
    a = 0;
    ret = _dp.do_parse(line, 0, a);
    _dp.do_parse(line, 3, s);
    EXPECT_NE(ret, goodcoder::DictParserRet::SUCCESS);
    EXPECT_EQ(a, 0);
    EXPECT_STREQ(s.c_str(), "1a2b3c");
    // Line #4
    std::getline(fin, line);
    b = 0;
    ret = _dp.do_parse(line, 1, b);
    _dp.do_parse(line, 3, s);
    EXPECT_NE(ret, goodcoder::DictParserRet::SUCCESS);
    EXPECT_EQ(b, 0);
    EXPECT_STREQ(s.c_str(), "");
}

}
