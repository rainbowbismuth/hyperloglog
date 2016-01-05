#include <iostream>
#include <fstream>
#include "hyperloglog.h"

int main() {
    emi::HyperLogLogCtx<std::string> ctx;
    std::ifstream ifs("/usr/share/dict/words");
    std::string input;
    while (ifs) {
        std::getline(ifs, input);
        ctx.add(input);
    }
    auto distinct = ctx.finish();
    std::cout << "Distinct: " << distinct << std::endl;
    return 0;
}