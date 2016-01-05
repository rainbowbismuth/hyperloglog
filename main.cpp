#include <iostream>
#include <fstream>
#include "hyperloglog.h"
#include <vector>

int main() {
    std::vector<std::string> words;
    std::ifstream ifs("/usr/share/dict/words");
    std::string input;
    while (ifs) {
        std::getline(ifs, input);
        words.push_back(input);
    }

    typedef std::vector<std::string>::iterator iter;
    typedef std::hash<std::string> hash;

#define TEST(n) \
    {\
        auto distinct = emi::HyperLogLog<iter, hash, (n)>(words.begin(), words.end());\
        std::cout << (1<<(n)) << ": " << distinct;\
        std::cout << " (error " << (std::abs(distinct - words.size()) / words.size()) * 100 << "%)";\
        std::cout << std::endl;\
    }\

    TEST(1);
    TEST(2);
    TEST(3);
    TEST(4);
    TEST(5);
    TEST(6);
    TEST(7);
    TEST(8);
    TEST(9);
    TEST(10);
    TEST(11);
    TEST(12);
    return 0;
}